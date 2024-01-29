import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * The Property class represents a property. It contains information about
 * the property, such as its property ID, number of bedrooms, number of rooms, city, price per day,
 * and the host ID associated with the property.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 */
public abstract class Property implements Comparable {
    private int propertyId;
    private int noBedRooms;
    private int noRooms;
    private String city;
    private double pricePerDay;
    private HashMap<Date, String> inspections;
    private Host belongsTo;


    /**
     * Constructs a Property with the specified details.
     *
     * This constructor initializes a Property object with the provided property ID, number of bedrooms, number of rooms,
     * city, price per day, and inspection details. It sets the values of these properties based on the parameters
     * passed to the constructor.
     *
     * @param propertyId    The unique identifier of the property.
     * @param noBedRooms    The number of bedrooms in the property.
     * @param noRooms       The total number of rooms in the property.
     * @param city          The city where the property is located.
     * @param pricePerDay   The price per day for renting the property.
     * @param date          The date of the inspection.
     * @param inspectionReview The review of inspection.
     */
    public Property(int propertyId, int noBedRooms, int noRooms, String city, double pricePerDay, Date date, String inspectionReview) {
        this.propertyId = propertyId;
        this.noBedRooms = noBedRooms;
        this.noRooms = noRooms;
        this.city = city;
        this.pricePerDay = pricePerDay;
        this.inspections = new HashMap<>();
        this.inspections.put(date, inspectionReview);
    }

    /**
     * Construct the property with specified parameters.
     * @param propertyId The unique identifier of the property.
     * @param noBedRooms The number of bedrooms.
     * @param noRooms The number of rooms.
     * @param city The city.
     * @param pricePerDay The price per day.
     */
    public Property(int propertyId, int noBedRooms, int noRooms, String city, double pricePerDay) {
        this.propertyId = propertyId;
        this.noBedRooms = noBedRooms;
        this.noRooms = noRooms;
        this.city = city;
        this.pricePerDay = pricePerDay;
        this.inspections = new HashMap<>();
    }

    /**
     * Default constructor.
     */
    public Property() {
    }

    /**
     * Constructs a Property with the specified details.
     *
     * This constructor initializes a Property object with the provided property ID, number of bedrooms, number of rooms,
     * city, and price per day. It sets the values of these properties based on the parameters
     * passed to the constructor.
     *
     * @param propertyId    The unique identifier of the property.
     * @param noBedRooms    The number of bedrooms in the property.
     * @param noRooms       The total number of rooms in the property.
     * @param city          The city where the property is located.
     * @param pricePerDay   The price per day for renting the property.
     * @param belongsTo     The host of the property.
     */
    public Property(int propertyId, int noBedRooms, int noRooms, String city, double pricePerDay, Host belongsTo) {
        this.propertyId = propertyId;
        this.noBedRooms = noBedRooms;
        this.noRooms = noRooms;
        this.city = city;
        this.pricePerDay = pricePerDay;
        this.belongsTo = belongsTo;
        this.inspections = new HashMap<>();
    }

    /**
     * Gets the unique identifier of the property.
     *
     * @return The property ID.
     */
    public int getPropertyId() {
        return propertyId;
    }

    /**
     * Sets the unique identifier of the property.
     *
     * @param propertyId The new property ID to be set.
     */
    public void setPropertyId(int propertyId) {
        this.propertyId = propertyId;
    }

    /**
     * Gets the number of bedrooms in the property.
     *
     * @return The number of bedrooms.
     */
    public int getNoBedRooms() {
        return noBedRooms;
    }

    /**
     * Sets the number of bedrooms in the property.
     *
     * @param noBedRooms The new number of bedrooms to be set.
     */
    public void setNoBedRooms(int noBedRooms) {
        this.noBedRooms = noBedRooms;
    }

    /**
     * Gets the total number of rooms in the property.
     *
     * @return The total number of rooms.
     */
    public int getNoRooms() {
        return noRooms;
    }

    /**
     * Sets the total number of rooms in the property.
     *
     * @param noRooms The new total number of rooms to be set.
     */
    public void setNoRooms(int noRooms) {
        this.noRooms = noRooms;
    }

    /**
     * Gets the city where the property is located.
     *
     * @return The city name.
     */
    public String getCity() {
        return city;
    }

    /**
     * Sets the city where the property is located.
     *
     * @param city The new city name to be set.
     */
    public void setCity(String city) {
        this.city = city;
    }

    /**
     * Gets the price per day for renting the property.
     *
     * @return The price per day.
     */
    public double getPricePerDay() {
        return pricePerDay;
    }

    /**
     * Sets the price per day for renting the property.
     *
     * @param pricePerDay The new price per day to be set.
     */
    public void setPricePerDay(double pricePerDay) {
        this.pricePerDay = pricePerDay;
    }

    /**
     * Gets the inspection details for the property.
     *
     * @return A HashMap containing inspection details.
     */
    public HashMap getInspections() {
        return inspections;
    }

    /**
     * Sets the inspection details for the property.
     *
     * @param inspections A HashMap containing inspection details to be set.
     *                   The keys and values in the HashMap depend on the specific requirements for property inspection.
     */
    public void setInspections(HashMap inspections) {
        this.inspections = inspections;
    }

    /**
     * Get the host of the property.
     * @return The host.
     */
    public Host getBelongsTo() {
        return belongsTo;
    }

    /**
     * Set the host of the property.
     * @param belongsTo The new host to be set.
     */
    public void setBelongsTo(Host belongsTo) {
        this.belongsTo = belongsTo;
    }

    /**
     * Print the property.
     * @return The template string of property.
     */
    @Override
    public String toString() {
        return "\n--------Property Info------" +
                "\nProperty ID: " + propertyId +
                "\nNumber of Bedrooms: " + noBedRooms +
                "\nNumber of rooms: " + noRooms +
                "\nCity: " + city +
                "\nPrice Per Day: " + pricePerDay +
                "\nInspections: " + inspections +
                "\nHost: " + belongsTo +
                "\n----------------------------";
    }

    public abstract double calculatePricePerDay();

    /**
     * Display the inspections in a format.
     * @return The string template of inspections
     */
    public String displayInspections() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        StringBuilder result = new StringBuilder();
        for (Map.Entry<Date, String> entry: inspections.entrySet()) {
            result.append(dateFormat.format(entry.getKey())).append(" - ").append(entry.getValue()).append("\n");
        }

        return String.valueOf(result);
    }

    /**
     * Implement the compareTo method defined in Comparable
     * @param property The property to be compared.
     * @return 1 if it is greater, -1 if it is less, 0 if it is equal.
     */
    public int compareTo(Property property) {
        if (this.calculatePricePerDay() > property.calculatePricePerDay()) {
            return 1;
        } else if (this.calculatePricePerDay() < property.calculatePricePerDay()) {
            return -1;
        } else {
            return 0;
        }
    }
}
