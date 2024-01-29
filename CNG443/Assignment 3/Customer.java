import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

/**
 * An abstract class representing a customer, extending the base User class.
 *
 * This class includes information about the customer's preferred payment method in addition to basic user details.
 * Subclasses are expected to implement the abstract method `discountPercentage` to calculate discounts.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 */
public abstract class Customer extends User {
    private String preferredPaymentMethod;
    private ArrayList<Booking> bookings = new ArrayList<Booking>();

    /**
     * Default constructor.
     */
    public Customer() {}

    /**
     * Construct a user with the specified user ID, first name, last name,
     * registration date, date of birth and preferred payment method.
     *
     * @param userId The user ID.
     * @param dateOfBirth The date of birth of the user.
     * @param firstName The first name of the user.
     * @param lastName The last name of the user.
     * @param registrationDate The registration date of the user.
     * @param preferredPaymentMethod The preferred payment method of the user.
     */
    public Customer(int userId, Date dateOfBirth, String firstName, String lastName, Date registrationDate, String preferredPaymentMethod) {
        super(userId, dateOfBirth, firstName, lastName, registrationDate);
        this.preferredPaymentMethod = preferredPaymentMethod;
    }

    /**
     * Construct a user with the specified user ID, first name, last name, and preferred payment method.
     * @param userId The user ID.
     * @param firstName The first name of the user.
     * @param lastName The last name of the user.
     * @param preferredPaymentMethod The preferred payment method of the user.
     */
    public Customer(int userId, String firstName, String lastName, String preferredPaymentMethod) {
        super(userId, firstName, lastName);
        this.preferredPaymentMethod = preferredPaymentMethod;
    }

    /**
     * Get the preferred payment method of the user.
     * @return The preferred method of the user.
     */
    public String getPreferredPaymentMethod() {
        return preferredPaymentMethod;
    }

    /**
     * Set the preferred payment method.
     * @param preferredPaymentMethod The new preferred payment method to be set.
     */
    public void setPreferredPaymentMethod(String preferredPaymentMethod) {
        this.preferredPaymentMethod = preferredPaymentMethod;
    }

    /**
     * Get the bookings.
     * @return
     */
    public ArrayList<Booking> getBookings() {
        return bookings;
    }

    /**
     * Set the bookings.
     * @param bookings The new bookings to be set.
     */
    public void setBookings(ArrayList<Booking> bookings) {
        this.bookings = bookings;
    }

    /**
     * Add a booking.
     * @param booking The booking will be added.
     */
    public void addBooking(Booking booking) {
        bookings.add(booking);
    }

    /**
     * Print the Customer.
     * @return Template string of Customer.
     */
    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        String formattedBirthday = dateFormat.format(super.getDateOfBirth());
        String formattedRegistrationDate = dateFormat.format(super.getRegistrationDate());
        return "\n--------User Info---------" +
                "\nUser ID: " + super.getUserId() +
                "\nBirthday: " + formattedBirthday +
                "\nFirst name: " + super.getFirstName() +
                "\nLast name: " + super.getLastName() +
                "\nRegistration date: " + formattedRegistrationDate +
                "\nPreferred payment method: " + preferredPaymentMethod +
                "\n-------------------------\n";
    }

    /**
     * Abstract method of discount percentage.
     * @return Discount percentage.
     */
    public abstract double discountPercentage();
}
