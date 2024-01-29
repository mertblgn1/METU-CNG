import java.util.ArrayList;
import java.util.Date;

/**
 * The User class represents a user in the booking system. Users can make bookings for properties.
 * It contains information about the user, such as their user ID, date of birth, first name, last name,
 * date of birth, and a list of bookings associated with the user.
 */
public class User {
    private int userId;
    private Date dateOfBirth;
    private String firstName;
    private String lastName;
    private ArrayList<Booking> bookings = new ArrayList<Booking>();

    /** Construct a User with the specified userId, dateOfBirth, firstName and lastName
     */
    public User(int userId, Date dateOfBirth, String firstName, String lastName) {
        this.userId = userId;
        this.dateOfBirth = dateOfBirth;
        this.firstName = firstName;
        this.lastName = lastName;
    }

    /** Construct a User with the specified userId, firstName and lastName
     */
    public User(int userId, String firstName, String lastName) {
        dateOfBirth = new Date();
        this.userId = userId;
        this.firstName = firstName;
        this.lastName = lastName;
    }

    /** Default constructor.
     */
    public User() {
    }

    /** Return bookings list
     */
    public ArrayList<Booking> getBookings() {
        return bookings;
    }

    /** Return userId
     */
    public int getUserId() {
        return userId;
    }

    /** Return dateOfBirth
     */
    public Date getDateOfBirth() {
        return dateOfBirth;
    }

    /** Return firstName
     */
    public String getFirstName() {
        return firstName;
    }

    /** Return lastName
     */
    public String getLastName() {
        return lastName;
    }

    /** Set the userId
     */
    public void setUserId(int userId) {
        this.userId = userId;
    }

    /** Set the dateOfBirth
     */
    public void setDateOfBirth(Date dateOfBirth) {
        this.dateOfBirth = dateOfBirth;
    }

    /** Set the firstName
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /** Set the lastName
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    /** Set the bookings list
     */
    public void setBookings(ArrayList<Booking> bookings) {
        this.bookings = bookings;
    }

    /** Add a booking to the bookings list
     */
    public void addBooking(Booking booking) {
        bookings.add(booking);
    }
}
