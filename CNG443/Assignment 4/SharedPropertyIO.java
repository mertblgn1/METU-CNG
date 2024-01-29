import java.io.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * Write and read shared properties
 */
public class SharedPropertyIO {
    public static void writeToFile(ArrayList<Property> properties) {
        try (DataOutputStream dataOutputStream = new DataOutputStream(new FileOutputStream("sharedProperty.dat"))) {
            // Extract the shared properties from the properties list
            ArrayList<SharedProperty> sharedProperties = new ArrayList<>();
            for (Property property : properties) {
                if (property instanceof SharedProperty) {
                    sharedProperties.add((SharedProperty) property);
                }
            }

            // Write the number of properties to the file
            dataOutputStream.writeInt(sharedProperties.size());

            // Write each property's data to the file
            for (SharedProperty sharedProperty : sharedProperties) {
                dataOutputStream.writeInt(sharedProperty.getPropertyId());
                dataOutputStream.writeInt(sharedProperty.getNoBedRooms());
                dataOutputStream.writeInt(sharedProperty.getNoRooms());
                dataOutputStream.writeUTF(sharedProperty.getCity());
                dataOutputStream.writeDouble(sharedProperty.getPricePerDay());
                dataOutputStream.writeInt(sharedProperty.getBelongsTo().getUserId());

                // Write inspections
                Map<Date, String> inspections = sharedProperty.getInspections();
                dataOutputStream.writeInt(inspections.size());

                for (Map.Entry<Date, String> entry: inspections.entrySet()) {
                    dataOutputStream.writeLong(entry.getKey().getTime());
                    dataOutputStream.writeUTF(entry.getValue());
                }

            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static ArrayList<Property> readFromFile() {
        ArrayList<Property> sharedProperties = new ArrayList<>();

        try (DataInputStream dataInputStream = new DataInputStream(new FileInputStream("sharedProperty.dat"))) {
            // Read the number of users from the file
            int numProperties = dataInputStream.readInt();

            // Read each user's data from the file
            for (int i = 0; i < numProperties; i++) {
                int propertyId = dataInputStream.readInt();
                int noBedrooms = dataInputStream.readInt();
                int noRooms = dataInputStream.readInt();
                String city = dataInputStream.readUTF();
                double pricePerDay = dataInputStream.readDouble();
                int hostId = dataInputStream.readInt();

                // Read the number of inspections
                int numInspections = dataInputStream.readInt();

                // Create a HashMap to store inspections
                Map<Date, String> inspections = new HashMap<>();

                // Read each inspection entry
                for (int j = 0; j < numInspections; j++) {
                    long inspectionDateMillis = dataInputStream.readLong();
                    Date inspectionDate = new Date(inspectionDateMillis);
                    String inspectionDetails = dataInputStream.readUTF();
                    inspections.put(inspectionDate, inspectionDetails);
                }

                // Add inspections
                SharedProperty sharedProperty = new SharedProperty(propertyId, noBedrooms, noRooms, city, pricePerDay, BASIC.getHost(hostId));
                for (Map.Entry<Date, String> entry : inspections.entrySet()) {
                    String inspectionDetails = entry.getValue();

                    BASIC.addInspectionToProperty(propertyId, inspectionDetails);
                }
                sharedProperties.add(sharedProperty);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
        return sharedProperties;
    }
}
