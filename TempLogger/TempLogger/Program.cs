using System.Net;
using System.IO.Ports;
using System.IO;
using Device.Net;


//setup variables for listing USB devices
//getting arduino port
//setting file path


public class usbPort
{

    public int portNumber { get; set; }
    public string portName { get; set; }

    public usbPort(int portNum, string portName)
    {
        this.portNumber = portNum;
        this.portName = portName;
    }

}

public class usbComm
{
    public static void Main()
    {
        //Dictionary<string, string> usbDevices = new Dictionary<string, string>();

        //get all usbmodem ports added to this to filter
        List<usbPort> macUsbList = new List<usbPort>();
        //this will become the filtered list - either by default if only one usbmodem or by user selecing value of proper usbmodem
        List<string> multiUsbPorts = new List<string>();

        //string arduino will be our port name
        String arduino = "";
        //need to adjust this for users systems
        String filePath = Environment.GetFolderPath(Environment.SpecialFolder.Personal) + "/Documents";
        //temp fix is to use output folder from visual studio
        //String filePath = Environment.CurrentDirectory;
        String macPortSearch = "tty.usb";
        bool keepRead = true;

        SerialPort sp = new SerialPort();
        
        sp.BaudRate = 9600;

        //capture ctrl-c
        Console.CancelKeyPress += delegate
        {

        };

        //Console.WriteLine("Available Ports:");
        int x = 0;
        foreach (string s in SerialPort.GetPortNames())
        {
            macUsbList.Add(new usbPort(x, s));
            x++;
        }

        foreach(usbPort p in macUsbList)
        {
            if (p.portName.Contains(macPortSearch))
            {
                multiUsbPorts.Add(p.portName);

                //Console.WriteLine("Port Num: " + p.portNumber + " Port Name: " + p.portName);
            }
        }
        var localMacPorts = multiUsbPorts.Count();
        if(localMacPorts > 1)
        {
            foreach(var n in multiUsbPorts)
            {
                Console.WriteLine("pause: ");
            }
        }
        else
        {
            
            arduino = multiUsbPorts.FirstOrDefault();
            sp.PortName = arduino;
            //Console.WriteLine("Writing Log File to: " + filePath + "/LaserTempLog-" + DateTime.Now.ToString("MMMddyyyy-hhmmtt") + ".txt");
            //Console.WriteLine("Arduino port defaulted to only usbmodem found: " + arduino);
            //Console.WriteLine("Baud Rate: " + sp.BaudRate);
            //Console.WriteLine("sp.Portname : " + sp.PortName);

            using StreamWriter file = new StreamWriter(filePath + "/LaserTempLog-" + DateTime.Now.ToString("MMMddyyyy-hhmmtt") + ".txt");

            sp.Open();
            while (keepRead)
            {
                string message = sp.ReadLine();
                Console.WriteLine(message);
                file.WriteLine(message);
            }
            
            
            Console.WriteLine("pause");
        }
    }
    
}

