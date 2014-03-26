# Extensions for OneDrive

## About
Extensions for OneDrive currently adds:

* A "Copy OneDrive public link" context menu item
* A shell icon overlay to indicate state of cloud->local sync

## Download

See [Releases](https://github.com/riverar/ExtensionsForOneDrive/releases) for downloadable bits.

## Installation

Place all bits into a permanent folder (e.g. `C:\Program Files\Extensions for OneDrive`) and execute `Install.bat` (as a user with administrative privileges).

This will register the shell extension and [ngen](http://msdn.microsoft.com/en-us/library/6t9t5wcf.aspx) managed binaries for faster start up performance.

A restart of the shell is **not** required for first time users.

## Uninstallation

Execute `Uninstall.bat` (again, as a user with administrative privileges).

This will unregister the shell extension and remove any previously ngen'ed binaries.

Restart Windows to ensure you can delete all bits from their permanent location.
(You may instead resort to terminating and restarting all processes hosting the extension.)

## Looking to contribute?

I welcome everyone to peruse the code and suggest changes where needed.

In the short term, I'd like to:

* Improve (un)installation workflow
* Implement Clipboard-to-OneDrive to enable raw image data sharing scenarios
* Add another overlay handler to indicate "in the cloud" state
	* Ideally by not eating another shell icon overlay slot
* Clean up the service

## Support

Please use the issue tracker to submit any problems you run into. More general questions and comments can be directed to  me, [@WithinRafael](http://twitter.com/WithinRafael), on Twitter.

## Additional credits

Icon: "Cloud" by Pieter J. Smits from The Noun Project
http://thenounproject.com/term/cloud/6853/
