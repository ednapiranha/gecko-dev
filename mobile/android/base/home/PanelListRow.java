/* -*- Mode: Java; c-basic-offset: 4; tab-width: 20; indent-tabs-mode: nil; -*-
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.mozilla.gecko.home;

import android.util.Log;
import org.mozilla.gecko.favicons.Favicons;
import org.mozilla.gecko.R;
import org.mozilla.gecko.Tab;
import org.mozilla.gecko.Tabs;
import org.mozilla.gecko.db.BrowserContract.HomeItems;
import org.mozilla.gecko.favicons.OnFaviconLoadedListener;
import org.mozilla.gecko.util.ThreadUtils;
import org.mozilla.gecko.widget.FaviconView;

import com.squareup.picasso.Picasso;

import android.content.Context;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.view.View;
import android.widget.ImageView;

import java.lang.ref.WeakReference;

public class PanelListRow extends TwoLineRow {

    private final ImageView mIcon;

    public PanelListRow(Context context) {
        this(context, null);
    }

    public PanelListRow(Context context, AttributeSet attrs) {
        super(context, attrs);

        mIcon = (ImageView) findViewById(R.id.icon);
    }

    @Override
    public void updateFromCursor(Cursor cursor) {
        if (cursor == null) {
            return;
        }

        // XXX: This will have to be updated once we come up with the
        // final schema for Panel datasets (see bug 942288).

        int titleIndex = cursor.getColumnIndexOrThrow(HomeItems.TITLE);
        final String title = cursor.getString(titleIndex);
        setPrimaryText(title);

        int urlIndex = cursor.getColumnIndexOrThrow(HomeItems.URL);
        final String url = cursor.getString(urlIndex);
        setSecondaryText(url);

        int imageIndex = cursor.getColumnIndexOrThrow(HomeItems.IMAGE_URL);
        final String imageUrl = cursor.getString(imageIndex);

        Picasso.with(getContext())
               .load(imageUrl)
               .error(R.drawable.favicon)
               .into(mIcon);
    }
}
