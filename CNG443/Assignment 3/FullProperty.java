import java.util.Date;

/**
 * Represents a full property in the property management system.
 * Extends the base Property class and includes additional information about property size.
 */
public class FullProperty extends Property {
    private double propertySize;

    /**
     * Default constructor.
     */
    public FullProperty() {
    }

    /**
     * The constructor with the specified property size.
     * @param propertySize The property size.
     */
    public FullProperty(double propertySize) {
        this.propertySize = propertySize;
    }

    /**
     * Constructor with the specified parameters.
     *
     * @param propertyId The property ID.
     * @param noBedRooms The number of bedrooms.
     * @param noRooms The number of rooms.
     * @param city The city.
     * @param pricePerDay The price per day.
     * @param propertySize The property size.
     * @param host The host of property.
     */
    public FullProperty(int propertyId, int noBedRooms, int noRooms, String city, double pricePerDay, double propertySize, Host host) {
        super(propertyId, noBedRooms, noRooms, city, pricePerDay, host);
        this.propertySize = propertySize;
    }

    /**
     * Constructor with the specified parameters.
     *
     * @param propertyId The property ID.
     * @param noBedRooms The number of bedrooms.
     * @param noRooms The number of rooms.
     * @param city The city.
     * @param pricePerDay The price per day.
     * @param date The date of inspection.
     * @param inspectionReview The inspection text.
     * @param propertySize The property size.
     */
    public FullProperty(int propertyId, int noBedRooms, int noRooms, String city, double pricePerDay, Date date, String inspectionReview, double propertySize) {
        super(propertyId, noBedRooms, noRooms, city, pricePerDay, date, inspectionReview);
        this.propertySize = propertySize;
    }

    /**
     * Get the property size.
     * @return The property size.
     */
    public double getPropertySize() {
        return propertySize;
    }

    /**
     * Set the property size.
     * @param propertySize The property size to be set.
     */
    public void setPropertySize(double propertySize) {
        this.propertySize = propertySize;
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
                "\nType: Full property" +
                "\nProperty Size: " + propertySize +
                "\n----------------------------";
    }

    /**
     * Calculate the price per day.
     * If the property size is less than 200, the tax will be %1.
     * If the property size is between 200 and 300, the tax will be %3.
     * Else the tax will be %4.
     * @return The calculated price per day.
     */
    @Override
    public double calculatePricePerDay() {
        double result = super.getPricePerDay();
        if (propertySize < 200) {
            result += super.getPricePerDay() * 0.01;
        } else if (propertySize <= 300) {
            result += super.getPricePerDay() * 0.03;
        } else {
            result += super.getPricePerDay() * 0.04;
        }
        return result;
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
