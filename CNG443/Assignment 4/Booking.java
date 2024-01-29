import java.text.SimpleDateFormat;
import java.time.temporal.ChronoUnit;
import java.util.Date;

/**
 * Represents a booking with start and end dates, along with payment information.
 *
 * A booking may include information about whether the payment has been made or not. The class provides constructors
 * for creating bookings with different sets of information and getter and setter methods for accessing and modifying
 * the booking details.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 */
public class Booking {
    private Date startDate;
    private Date endDate;
    private boolean isPaid;
    private Property property;

    /**
     * Constructor with the specified start date, end date, property and payment information.
     * @param startDate Start date of the booking.
     * @param endDate End date of the booking.
     * @param isPaid Whether the payment is done.
     * @param property The property.
     */
    public Booking(Date startDate, Date endDate, boolean isPaid, Property property) {
        this.startDate = startDate;
        this.endDate = endDate;
        this.isPaid = isPaid;
        this.property = property;
    }

    /**
     * Constructor with the specified start date and end date.
     * @param startDate Start date of the booking.
     * @param endDate End date of the booking.
     */
    public Booking(Date startDate, Date endDate) {
        this.startDate = startDate;
        this.endDate = endDate;
    }

    /**
     * Default constructor.
     */
    public Booking() {
    }

    /**
     * Get the start date.
     * @return The start date.
     */
    public Date getStartDate() {
        return startDate;
    }

    /**
     * Set the start date.
     * @param startDate The new start date to be set.
     */
    public void setStartDate(Date startDate) {
        this.startDate = startDate;
    }

    /**
     * Get the end date.
     * @return The end date.
     */
    public Date getEndDate() {
        return endDate;
    }

    /**
     * Set the end date.
     * @param endDate The new end date to be set.
     */
    public void setEndDate(Date endDate) {
        this.endDate = endDate;
    }

    /**
     * Get if the payment is done.
     * @return True if payment is done, otherwise false.
     */
    public boolean isPaid() {
        return isPaid;
    }

    /**
     * Set the payment information.
     * @param paid The new payment information to be set.
     */
    public void setPaid(boolean paid) {
        isPaid = paid;
    }

    /**
     * Get the property.
     * @return The property.
     */
    public Property getProperty() {
        return property;
    }

    /**
     * Set the property.
     * @param property The new property to be set.
     */
    public void setProperty(Property property) {
        this.property = property;
    }

    /**
     * Calculate the total cost by calculating the difference of dates.
     * @return The total cost.
     */
    public double totalCost() {
        int days = (int) ChronoUnit.DAYS.between(endDate.toInstant(), startDate.toInstant());
        if (days < 0) days *= -1;
        return days * property.calculatePricePerDay();
    }

    /**
     * Display a booking in a template format.
     * @return The string template.
     */
    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        String formattedStartDate = dateFormat.format(startDate);
        String formattedEndDate = dateFormat.format(endDate);

        return "\n----- Booking Info -----" +
                "\nStart Date: " + formattedStartDate +
                "\nEnd Date: " + formattedEndDate +
                "\n------------------------";
    }
}
