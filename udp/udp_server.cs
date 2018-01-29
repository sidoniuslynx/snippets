using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;

namespace udpsvr
{
    class Program
    {
        static string stop_rcv = "!#stoprcv";
        static int rcv_port = 8998;
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            // var rcvd = Task.Run(() => Program.ReceivingJob(rcv_port));
            IPEndPoint rip = new IPEndPoint(IPAddress.Any, 0);
            try {
                using (UdpClient rcv = new UdpClient(rcv_port)) {

                    while (true) {
                        Byte[] rcved_bytes = rcv.Receive(ref rip);
                        string rcved_string = Encoding.ASCII.GetString(rcved_bytes);
                        if (rcved_string.StartsWith(stop_rcv)) {
                            Console.WriteLine("END ReceivingJob");
                            break;
                        } else {
                            // TODO: send to iot hub
                            Console.WriteLine($"Received message: [{rcved_string}]");
                        }
                    }
                }
            } catch (SocketException e) {
                Console.WriteLine(e.ToString());
            }
        }
    }
}
