import java.io.DataInputStream;
import java.io.DataOutputStream;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class EchoThread extends Thread
   {
     Socket clientSocket;

     public EchoThread(Socket clientSocket)
        {
          this.clientSocket = clientSocket;
        }


     public void run()
        {
          DataInputStream fromClient = null;
          DataOutputStream toClient = null;

          int charFromClient = 0;
          int state = 0;
          boolean keepGoing = true;

          System.out.println("Client connected...");

          try
            {
              fromClient = new DataInputStream(clientSocket.getInputStream());
              toClient = new DataOutputStream(clientSocket.getOutputStream());
            }
          catch(IOException e)
            {
               System.err.println("Error opening network streams");
               return;
            }

            while(keepGoing)
               {
                 try
                    {
                      charFromClient = fromClient.readByte();
                      System.out.print((char)charFromClient);
                    }
                 catch(IOException e)
                    {
                      System.err.println("Error reading character from client");
                      return;
                    }

                 try
                    {
                      toClient.writeByte(charFromClient);
                    }
                 catch(IOException e)
                    {
                      System.err.println("Error writing character to client");
                      return;
                    }

                 if(charFromClient == 'q')
                    {
                      System.out.println("\nBailing out!");
                      keepGoing = false;
                    }
               }

             try
                {
                  clientSocket.close();
                }
             catch(IOException e)
                {
                  System.err.println("Error closing socket to client");
                }
            }
       }