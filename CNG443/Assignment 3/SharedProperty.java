import java.util.Date;

/**
 * Represents a shared property, a type of property where multiple rooms are available for booking.
 * Extends the abstract class 'Property' and implements the 'PropertyPrice' interface.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 */
public class SharedProperty extends Property {
    /**
     * Constructs a shared property with detailed information, including inspections.
     *
     * @param propertyId       The unique identifier for the property.
     * @param noBedRooms       The number of bedrooms in the property.
     * @param noRooms          The total number of rooms available for booking.
     * @param city             The city where the property is located.
     * @param pricePerDay      The base price per day for the property.
     * @param date             The date of inspection.
     * @param inspectionReview The review from the inspection.
     */
    public SharedProperty(int propertyId, int noBedRooms, int noRooms, String city, double pricePerDay, Date date, String inspectionReview) {
        super(propertyId, noBedRooms, noRooms, city, pricePerDay, date, inspectionReview);
    }

    /**
     * Default constructor for a shared property.
     */
    public SharedProperty() {
    }

    /**
     * Constructs a shared property with essential information.
     *
     * @param propertyId The unique identifier for the property.
     * @param noBedRooms The number of bedrooms in the property.
     * @param noRooms    The total number of rooms available for booking.
     * @param city       The city where the property is located.
     * @param pricePerDay The base price per day for the property.
     * @param host       The host associated with the property.
     */
    public SharedProperty(int propertyId, int noBedRooms, int noRooms, String city, double pricePerDay, Host host, Date date, String inspectionReview) {
        super(propertyId, noBedRooms, noRooms, city, pricePerDay, host, date, inspectionReview);
    }

    public SharedProperty(int propertyId, int noBedrooms, int noRooms, String city, double pricePerDay, Host host) {
        super(propertyId, noBedrooms, noRooms, city, pricePerDay, host);
    }


    /**
     * Print the property.
     * @return The template string of property.
     */
    @Override
    public String toString() {
        return "\n--------Property Info------" +
                "\nProperty ID: " + super.getPropertyId() +
                "\nNumber of Bedrooms: " + super.getNoBedRooms() +
                "\nNumber of rooms: " + super.getNoRooms() +
                "\nCity: " + super.getCity() +
                "\nPrice Per Day: " + super.getPricePerDay() +
                "\nInspections: \n" + super.displayInspections() +
                "\nHost: " + super.getBelongsTo() +
                "\nType: Shared property" +
                "\n----------------------------";
    }

    /**
     * Calculates the price per day for a shared property by dividing the base price by the number of rooms.
     *
     * @return The calculated price per day for the shared property.
     */
    @Override
    public double calculatePricePerDay() {
        return super.getPricePerDay() / super.getNoRooms();
    }

    @Override
    public int compareTo(Object o) {
        if (this.calculatePricePerDay() > ((Property) o).calculatePricePerDay()) {
            return 1;
        } else if (this.calculatePricePerDay() < ((Property) o).calculatePricePerDay()) {
            return -1;
        } else {
            return 0;
        }
    }
}
