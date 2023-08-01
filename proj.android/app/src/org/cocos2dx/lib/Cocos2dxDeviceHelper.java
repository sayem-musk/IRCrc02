package org.cocos2dx.lib;

import org.cocos2dx.lib.Cocos2dxHelper;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Build;
import android.os.Vibrator;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.provider.MediaStore;
import android.provider.MediaStore.Images.Media;
import android.text.format.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Calendar;

import android.content.ContentValues;
import android.webkit.MimeTypeMap;

import android.util.Log;
import java.io.OutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileOutputStream;

public class Cocos2dxDeviceHelper {

	public static String getApplicationName() {
		PackageManager pm = Cocos2dxHelper.getActivity().getPackageManager();
		ApplicationInfo aInfo;
		try {
			aInfo = pm.getApplicationInfo( Cocos2dxHelper.getCocos2dxPackageName(), 0);
		} catch (final NameNotFoundException e) {
			aInfo = null;
		}
		return (aInfo != null ? (String)pm.getApplicationLabel(aInfo) : null);
	}
	
	public static String getPackageVersionName() {
		PackageManager pm = Cocos2dxHelper.getActivity().getPackageManager();
		PackageInfo pInfo;
		try {
			pInfo = pm.getPackageInfo( Cocos2dxHelper.getCocos2dxPackageName(), 0);
		} catch (final NameNotFoundException e) {
			pInfo = null;
		}
		return (pInfo != null ? (String)pInfo.versionName : null );
	}
	
	public static String getPackageVersionCode() {
		PackageManager pm = Cocos2dxHelper.getActivity().getPackageManager();
		PackageInfo pInfo;
		try {
			pInfo = pm.getPackageInfo( Cocos2dxHelper.getCocos2dxPackageName(), 0);
		} catch (final NameNotFoundException e) {
			pInfo = null;
		}
		return (pInfo != null ? Integer.toString(pInfo.versionCode) : null );
	}
	
	public static String getDeviceModel(){
		return Build.MODEL;
	}
	
	public static String getDeviceSystemVersion(){
		return Build.VERSION.RELEASE;
	}
	
	public static String getUserAgent(){
		return System.getProperty("http.agent");
	}
	
	public static boolean canVibrate() {
		Vibrator vib = (Vibrator) Cocos2dxHelper.getActivity().getSystemService(Context.VIBRATOR_SERVICE);
		/*
		 if( Build.VERSION.SDK_INT >= 11) {
		 //Only run Vibrator if present
		 if(vib!=null && Shaker.canShake(vbr))
		 return true;
		 } else if(vib!=null) {
		 //Before honeycomb, assume Vibrator present
		 return true;
		 }
		 return false;
		 */
		
		/*
		 int sdk=new Integer(Build.VERSION.SDK).intValue();
		 if (sdk < 11) return (vib != null);
		 else {
		 try {
		 return vib.hasVibrator();
		 } catch (IOException ie) {
		 return true;
		 }
		 }
		 /*
		 try {
		 return vib.hasVibrator();
		 } catch (IOException ie) {
		 return true;
		 }
		 */
		return (vib != null);
	}
	
	public static void vibrate(int milliseconds) {
		Vibrator vib = (Vibrator) Cocos2dxHelper.getActivity().getSystemService(Context.VIBRATOR_SERVICE);
		vib.vibrate(milliseconds);
	}

	public static void cropImageFile(String fullpath, int x, int y, int w, int h) {
		Log.d("TWDevice","cropImageFile (Java): local file is " + fullpath + " [NEEDS TESTING!!!!]");

		// load, crop, save back out
		Bitmap bitmap = BitmapFactory.decodeFile( fullpath );
		int bWidth = bitmap.getWidth();
		int bHeight = bitmap.getHeight();

		if ((x == 0) && (y == 0) && (w == bWidth) && (h == bHeight)) return;
		
		int cx = x;
		int cy = y;
		int cw = w;
		int ch = h;
		
		// fix values if out of bounds
		if (cx < 0.0) {
			cw += cx;
			cx = 0;
		}
		if (cy < 0) {
			ch += cy;
			cy = 0;
		}
		
		if (bWidth < (cx + cw)) cw = bWidth - cx;
		if (bHeight < (cy + ch)) ch = bHeight - cy;
		
		if ((cy != 0) || (ch != bHeight)) {
			// correct y
			cy = bHeight - ch - cy;
		}
		
		Bitmap cBitmap = Bitmap.createBitmap(bitmap, cx, cy, cw, ch);
		// save out

		FileOutputStream out = null;
		try {
			out = new FileOutputStream(fullpath);
			cBitmap.compress(Bitmap.CompressFormat.PNG, 100, out);
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				if (out != null) {
					out.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public static void saveToMediaStore(String fullpath) {
		// mPackageName = getApplication().getPackageName();

		Log.d("TWDevice","saveToMediaStore (Java): local file is " + fullpath );
		String ttl = fullpath.substring(fullpath.lastIndexOf("/")+1);

		// Date today = Calendar.getInstance().getTime();
		// SimpleDateFormat df = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
		// String reportDate = df.format(today);
		// long now = System.currentTimeMillis();

		String type = null;
		String extension = MimeTypeMap.getFileExtensionFromUrl(fullpath);
		if (extension != null) {
			MimeTypeMap mime = MimeTypeMap.getSingleton();
			type = mime.getMimeTypeFromExtension(extension);
		}
		if (! type.equals("image/png")) type = "image/jpg";

		Log.d("TWDevice","saveToMediaStore (Java): file type is " + type );

		Bitmap bitmap = BitmapFactory.decodeFile( fullpath );

  		ContentValues values=new ContentValues();
		values.put(Media.TITLE,ttl);
		values.put(Media.DATE_ADDED,System.currentTimeMillis());
		values.put(Media.MIME_TYPE, type);
		Uri uri = Cocos2dxHelper.getActivity().getContentResolver().insert(Media.EXTERNAL_CONTENT_URI,values);
		try {
			OutputStream outStream=Cocos2dxHelper.getActivity().getContentResolver().openOutputStream(uri);
			if (! type.equals("image/png"))
				bitmap.compress(Bitmap.CompressFormat.PNG,100,outStream);
			else bitmap.compress(Bitmap.CompressFormat.JPEG,100,outStream);
			// note saves to jpg anyway?
			outStream.flush();
			outStream.close();
			// Toast message=Toast.makeText(getContext(),R.string.message_saved,Toast.LENGTH_SHORT);
			// message.setGravity(Gravity.CENTER,message.getXOffset() / 2,message.getYOffset() / 2);
			// message.show();
			Log.d("TWDevice","saveToMediaStore (Java): saved to " + uri );
		}
		catch (  IOException ex) {
			// Toast message=Toast.makeText(getContext(),R.string.message_error_saving,Toast.LENGTH_SHORT);
			// message.setGravity(Gravity.CENTER,message.getXOffset() / 2,message.getYOffset() / 2);
			// message.show();
			Log.d("TWDevice","saveToMediaStore (Java): Failed to save file" );
		}
	}
}
