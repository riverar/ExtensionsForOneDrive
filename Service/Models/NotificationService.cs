using System;
using System.Windows.Forms;

namespace ExtensionsForOneDrive.Service.Models
{
	public interface INotificationService
	{
		void Notify(string message);
	}

	public class NotificationService : INotificationService
	{
		private readonly NotifyIcon _icon;

		public NotificationService()
		{
			_icon = new NotifyIcon();
			_icon.Icon = Assets.Cloud;
		}

		public void Notify(string message)
		{
			_icon.Visible = true;

			_icon.ShowBalloonTip(3000, "Extensions for OneDrive", message, ToolTipIcon.Info);
			_icon.BalloonTipShown += (_, __) =>
			{
				_icon.Visible = false;
			};
		}
	}
}
