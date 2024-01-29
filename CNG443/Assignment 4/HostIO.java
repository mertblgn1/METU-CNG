import java.io.*;
import java.util.ArrayList;
import java.util.Date;

/**
 * Write and read hosts
 */
public class HostIO {
    public static void writeToFile(ArrayList<User> users) {
        try (DataOutputStream dataOutputStream = new DataOutputStream(new FileOutputStream("host.dat"))) {
            // Extract the gold users from the users list
            ArrayList<Host> hosts = new ArrayList<>();
            for (User user : users) {
                if (user instanceof Host) {
                    hosts.add((Host) user);
                }
            }

            // Write the number of users to the file
            dataOutputStream.writeInt(hosts.size());

            // Write each user's data to the file
            for (Host host : hosts) {
                dataOutputStream.writeInt(host.getUserId());
                dataOutputStream.writeLong(host.getDateOfBirth().getTime());
                dataOutputStream.writeUTF(host.getFirstName());
                dataOutputStream.writeUTF(host.getLastName());
                dataOutputStream.writeLong(host.getRegistrationDate().getTime());
                dataOutputStream.writeDouble(host.getTaxNumber());
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static ArrayList<User> readFromFile() {
        ArrayList<User> hosts = new ArrayList<>();

        try (DataInputStream dataInputStream = new DataInputStream(new FileInputStream("host.dat"))) {
            // Read the number of users from the file
            int numUsers = dataInputStream.readInt();

            // Read each user's data from the file
            for (int i = 0; i < numUsers; i++) {
                int userId = dataInputStream.readInt();
                long dobMillis = dataInputStream.readLong();
                String firstName = dataInputStream.readUTF();
                String lastName = dataInputStream.readUTF();
                long regDateMillis = dataInputStream.readLong();

                // Convert millis to Date
                Date dob = new Date(dobMillis);
                Date regDate = new Date(regDateMillis);

                double taxNumber = dataInputStream.readDouble();
                hosts.add(new Host(userId, dob, firstName, lastName, regDate, taxNumber));
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
        return hosts;
    }
}
