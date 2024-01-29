/**
 * The Property class represents a property. It contains information about
 * the property, such as its property ID, number of bedrooms, number of rooms, city, price per day,
 * and the host ID associated with the property.
 */
public class Property {
    private int propertyId;
    private int noBedrooms;
    private int noRooms;
    private String city;
    private float pricePerDay;
    private int hostId;

    /** Construct a property with the specified
     * propertyId, noBedrooms, noRooms, city and pricePerDay
     */
    public Property(int propertyId, int noBedrooms, int noRooms, String city, float pricePerDay, int hostId) {
        this.propertyId = propertyId;
        this.noBedrooms = noBedrooms;
        this.noRooms = noRooms;
        this.city = city;
        this.pricePerDay = pricePerDay;
        this.hostId = hostId;
    }

    /** Construct a Property with the specified propertyId
     * Default values for noBedrooms and noRooms are 1, and default
     * value of city is an empty string. Also, pricePerDay is 0.
     */
    public Property(int propertyId, int hostId) {
        this.propertyId = propertyId;
        noBedrooms = 1;
        noRooms = 1;
        city = "";
        pricePerDay = 0;
        this.hostId = hostId;
    }

    /** Default constructor
     */
    public Property() {
    }

    /** Return propertyId
     */
    public int getPropertyId() {
        return propertyId;
    }

    /** Return number of bedrooms
     */
    public int getNoBedrooms() {
        return noBedrooms;
    }

    /** Return number of rooms
     */
    public int getNoRooms() {
        return noRooms;
    }

    /** Return the city
     */
    public String getCity() {
        return city;
    }

    /** Return the pricer per day
     */
    public float getPricePerDay() {
        return pricePerDay;
    }

    /** Return the hostId
     */
    public int getHostId() {
        return hostId;
    }

    /** Set propertyId
     */
    public void setPropertyId(int propertyId) {
        this.propertyId = propertyId;
    }

    /** Set number of bedrooms
     */
    public void setNoBedrooms(int noBedrooms) {
        this.noBedrooms = noBedrooms;
    }

    /** Set number of rooms
     */
    public void setNoRooms(int noRooms) {
        this.noRooms = noRooms;
    }

    /** Set the city
     */
    public void setCity(String city) {
        this.city = city;
    }

    /** Set the price per day
     */
    public void setPricePerDay(float pricePerDay) {
        this.pricePerDay = pricePerDay;
    }

    /** Set the hostId
     */
    public void setHostId(int hostId) {
        this.hostId = hostId;
    }
}
