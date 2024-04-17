package org.bitcoinluminarycore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class BitcoinLuminaryQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File bitcoinluminaryDir = new File(getFilesDir().getAbsolutePath() + "/.bitcoinluminary");
        if (!bitcoinluminaryDir.exists()) {
            bitcoinluminaryDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
