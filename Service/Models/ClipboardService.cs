using System;
using System.Windows;
using System.Threading;
using System.Security.Principal;
using System.Security.AccessControl;
using System.Threading.Tasks;

using ExtensionsForOneDrive.Service.Models;

namespace ExtensionsForOneDrive.Models
{
	// TODO: This entire class feels icky.

	public interface IClipboardService
	{
		void GetPublicLinkAndStore();
	}

	public class ClipboardService : IClipboardService
	{
		private readonly IConfigurationService _configurationService;
		private readonly ILiveService _liveService;
		private readonly INotificationService _notificationService;

		private Task _changeListenerTask;

		public ClipboardService(IConfigurationService configurationService, ILiveService liveService, INotificationService notificationService)
		{
			_configurationService = configurationService;
			_liveService = liveService;
			_notificationService = notificationService;

			ConfigureDropListener();
		}

		public void GetPublicLinkAndStore()
		{
			var link = _liveService.GetSharedReadLink(_configurationService.GetValue<string>("Drop"));

			var clipboardThread = new Thread(() => {
				Clipboard.SetText(link);
			});

			clipboardThread.SetApartmentState(ApartmentState.STA);
			clipboardThread.Start();

			_notificationService.Notify(string.Format("Public link saved to clipboard:\n{0}", link));
		}

		private void ConfigureDropListener()
		{
			var sid = new SecurityIdentifier(WellKnownSidType.BuiltinUsersSid, null);
			var accessRule = new EventWaitHandleAccessRule(sid, EventWaitHandleRights.Synchronize | EventWaitHandleRights.Modify, AccessControlType.Allow);

			var security = new EventWaitHandleSecurity();
			security.AddAccessRule(accessRule);

			bool newlyCreated = false;
			var waitHandle = new EventWaitHandle(false, EventResetMode.AutoReset, "ExtensionsForOneDrive_DataAvailableEvent", out newlyCreated, security);

			if (!newlyCreated)
			{
				throw new InvalidOperationException("Configuration Changed event already exists.");
			}

			_changeListenerTask = Task.Factory.StartNew(() =>
			{
				while (waitHandle.WaitOne())
				{
					GetPublicLinkAndStore();
				}
			});
		}
	}
}
