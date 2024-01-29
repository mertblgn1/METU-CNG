import java.io.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * Write and read full properties
 */
public class FullPropertyIO {
    public static void writeToFile(ArrayList<Property> properties) {
        try (DataOutputStream dataOutputStream = new DataOutputStream(new FileOutputStream("fullProperty.dat"))) {
            // Extract the shared properties from the properties list
            ArrayList<FullProperty> fullProperties = new ArrayList<>();
            for (Property property : properties) {
                if (property instanceof FullProperty) {
                    fullProperties.add((FullProperty) property);
                }
            }

            // Write the number of properties to the file
            dataOutputStream.writeInt(fullProperties.size());

            // Write each property's data to the file
            for (FullProperty fullProperty : fullProperties) {
                dataOutputStream.writeInt(fullProperty.getPropertyId());
                dataOutputStream.writeInt(fullProperty.getNoBedRooms());
                dataOutputStream.writeInt(fullProperty.getNoRooms());
                dataOutputStream.writeUTF(fullProperty.getCity());
                dataOutputStream.writeDouble(fullProperty.getPricePerDay());
                dataOutputStream.writeInt(fullProperty.getBelongsTo().getUserId());
                dataOutputStream.writeDouble(fullProperty.getPropertySize());

                // Write inspections
                Map<Date, String> inspections = fullProperty.getInspections();
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
        ArrayList<Property> fullProperties = new ArrayList<>();

        try (DataInputStream dataInputStream = new DataInputStream(new FileInputStream("fullProperty.dat"))) {
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
                double propertySize = dataInputStream.readDouble();

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
                FullProperty fullProperty = new FullProperty(propertyId, noBedrooms, noRooms, city, pricePerDay, propertySize, BASIC.getHost(hostId));
                for (Map.Entry<Date, String> entry : inspections.entrySet()) {
                    String inspectionDetails = entry.getValue();

                    BASIC.addInspectionToProperty(propertyId, inspectionDetails);
                }
                fullProperties.add(fullProperty);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
        return fullProperties;
    }
}
