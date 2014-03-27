namespace ExtensionsForOneDrive
{
    public class CloseLoginWindow
    {
        public CloseLoginWindow(bool continueProcessing)
        {
            this.ContinueProcessing = continueProcessing;
        }

        public bool ContinueProcessing { get; private set; }
    }
}
