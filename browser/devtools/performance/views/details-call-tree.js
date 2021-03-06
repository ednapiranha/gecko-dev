/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
"use strict";

/**
 * CallTree view containing profiler call tree, controlled by DetailsView.
 */
let CallTreeView = {
  /**
   * Sets up the view with event binding.
   */
  initialize: function () {
    this._callTree = $(".call-tree-cells-container");
    this._onRecordingStopped = this._onRecordingStopped.bind(this);
    this._onRecordingSelected = this._onRecordingSelected.bind(this);
    this._onRangeChange = this._onRangeChange.bind(this);
    this._onLink = this._onLink.bind(this);

    PerformanceController.on(EVENTS.RECORDING_STOPPED, this._onRecordingStopped);
    PerformanceController.on(EVENTS.RECORDING_SELECTED, this._onRecordingSelected);
    OverviewView.on(EVENTS.OVERVIEW_RANGE_SELECTED, this._onRangeChange);
    OverviewView.on(EVENTS.OVERVIEW_RANGE_CLEARED, this._onRangeChange);
  },

  /**
   * Unbinds events.
   */
  destroy: function () {
    PerformanceController.off(EVENTS.RECORDING_STOPPED, this._onRecordingStopped);
    PerformanceController.off(EVENTS.RECORDING_SELECTED, this._onRecordingSelected);
    OverviewView.off(EVENTS.OVERVIEW_RANGE_SELECTED, this._onRangeChange);
    OverviewView.off(EVENTS.OVERVIEW_RANGE_CLEARED, this._onRangeChange);
  },

  /**
   * Method for handling all the set up for rendering a new call tree.
   */
  render: function (profilerData, beginAt, endAt, options={}) {
    // Empty recordings might yield no profiler data.
    if (profilerData.profile == null) {
      return;
    }
    let threadNode = this._prepareCallTree(profilerData, beginAt, endAt, options);
    this._populateCallTree(threadNode, options);
    this.emit(EVENTS.CALL_TREE_RENDERED);
  },

  /**
   * Called when recording is stopped.
   */
  _onRecordingStopped: function () {
    let profilerData = PerformanceController.getProfilerData();
    this.render(profilerData);
  },

  /**
   * Called when a recording has been selected.
   */
  _onRecordingSelected: function (_, recording) {
    // If not recording, then this recording is done and we can render all of it
    // Otherwise, TODO in bug 1120699 will hide the details view altogether if
    // this is still recording.
    if (!recording.isRecording()) {
      let profilerData = recording.getProfilerData();
      this.render(profilerData);
    }
  },

  /**
   * Fired when a range is selected or cleared in the OverviewView.
   */
  _onRangeChange: function (_, params) {
    // When a range is cleared, we'll have no beginAt/endAt data,
    // so the rebuild will just render all the data again.
    let profilerData = PerformanceController.getProfilerData();
    let { beginAt, endAt } = params || {};
    this.render(profilerData, beginAt, endAt);
  },

  /**
   * Fired on the "link" event for the call tree in this container.
   */
  _onLink: function (_, treeItem) {
    let { url, line } = treeItem.frame.getInfo();
    viewSourceInDebugger(url, line).then(
      () => this.emit(EVENTS.SOURCE_SHOWN_IN_JS_DEBUGGER),
      () => this.emit(EVENTS.SOURCE_NOT_FOUND_IN_JS_DEBUGGER));
  },

  /**
   * Called when the recording is stopped and prepares data to
   * populate the call tree.
   */
  _prepareCallTree: function (profilerData, beginAt, endAt, options) {
    let threadSamples = profilerData.profile.threads[0].samples;
    let contentOnly = !Prefs.showPlatformData;
    // TODO handle inverted tree bug 1102347
    let invertTree = false;

    let threadNode = new ThreadNode(threadSamples, contentOnly, beginAt, endAt, invertTree);
    options.inverted = invertTree && threadNode.samples > 0;

    return threadNode;
  },

  /**
   * Renders the call tree.
   */
  _populateCallTree: function (frameNode, options={}) {
    let root = new CallView({
      autoExpandDepth: options.inverted ? 0 : undefined,
      frame: frameNode,
      hidden: options.inverted,
      inverted: options.inverted
    });

    // Bind events
    root.on("link", this._onLink);

    // Clear out other call trees.
    this._callTree.innerHTML = "";
    root.attachTo(this._callTree);

    let contentOnly = !Prefs.showPlatformData;
    root.toggleCategories(!contentOnly);
  }
};

/**
 * Convenient way of emitting events from the view.
 */
EventEmitter.decorate(CallTreeView);

/**
 * Opens/selects the debugger in this toolbox and jumps to the specified
 * file name and line number.
 * @param string url
 * @param number line
 */
let viewSourceInDebugger = Task.async(function *(url, line) {
  // If the Debugger was already open, switch to it and try to show the
  // source immediately. Otherwise, initialize it and wait for the sources
  // to be added first.
  let debuggerAlreadyOpen = gToolbox.getPanel("jsdebugger");
  let { panelWin: dbg } = yield gToolbox.selectTool("jsdebugger");

  if (!debuggerAlreadyOpen) {
    yield dbg.once(dbg.EVENTS.SOURCES_ADDED);
  }

  let { DebuggerView } = dbg;
  let { Sources } = DebuggerView;

  let item = Sources.getItemForAttachment(a => a.source.url === url);
  if (item) {
    return DebuggerView.setEditorLocation(item.attachment.source.actor, line, { noDebug: true });
  }

  return Promise.reject("Couldn't find the specified source in the debugger.");
});
