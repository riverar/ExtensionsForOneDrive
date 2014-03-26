﻿using System.Drawing;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ExtensionsForOneDrive.Service.Utilities
{
	public static class Extensions
	{
		public static ImageSource ToImageSource(this Icon icon)
		{
			return Imaging.CreateBitmapSourceFromHIcon(icon.Handle, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
		}
	}
}
