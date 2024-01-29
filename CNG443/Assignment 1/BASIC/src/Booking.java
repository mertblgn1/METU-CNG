import java.util.Date;

/**
 * The Booking class represents a booking. It contains information about the booking, such as the start date,
 * end date, payment status, and the associated property.
 */
public class Booking {
    private Date startDate;
    private Date endDate;
    private boolean isPaid;
    private Property property;

    /** Construct a Booking with the specified startDate and endDate. Default isPaid is false.
     */
    public Booking(Date startDate, Date endDate, Property property) {
        this.startDate = startDate;
        this.endDate = endDate;
        this.property = property;
        this.isPaid = false;
    }

    /** Construct a Booking with the specified startDate, endDate and isPaid.
     */
    public Booking(Date startDate, Date endDate, boolean isPaid) {
        this.startDate = startDate;
        this.endDate = endDate;
        this.isPaid = isPaid;
    }

    /** Default constructor
     */
    public Booking() {
    }

    /** Return startDate
     */
    public Date getStartDate() {
        return startDate;
    }

    /** Return endDate
     */
    public Date getEndDate() {
        return endDate;
    }

    /** Return isPaid
     */
    public boolean isPaid() {
        return isPaid;
    }

    public int getPropertyId() {
        return property.getPropertyId();
    }

    /** Set the startDate
     */
    public void setStartDate(Date startDate) {
        this.startDate = startDate;
    }

    /** Set the endDate
     */
    public void setEndDate(Date endDate) {
        this.endDate = endDate;
    }

    /** Set the isPaid
     */
    public void setPaid(boolean isPaid) {
        this.isPaid = isPaid;
    }

    /**
     * Calculate the total number of days of the booking and multiplies it with the pricePerDay of the property.
     * @return Calculation result.
     */
    public float totalCost() {
        int days = endDate.getDay() - startDate.getDay();
        if (days < 0) days *= -1;
        return days * property.getPricePerDay();
    }
}
