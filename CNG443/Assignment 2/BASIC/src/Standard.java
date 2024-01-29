import java.text.SimpleDateFormat;
import java.time.Instant;
import java.time.LocalDate;
import java.time.ZoneId;
import java.time.temporal.ChronoUnit;
import java.util.Date;

/**
 * Represents a Standard-level customer, extending the Customer class.
 *
 * This class inherits basic customer information from the Customer class and provides constructors for
 * creating Standard customers with different sets of information. It also implements the abstract method
 * `discountPercentage` to calculate applicable discounts based on specific business logic for Standard customers.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 * @see Customer
 */
public class Standard extends Customer {
    /**
     * Default constructor.
     */
    public Standard() {
    }

    /**
     * Constructor with the specified user ID, date of birth, first name, last name,
     * registration date, preferred payment method and gold level.
     * @param userId User ID.
     * @param dateOfBirth Date of birth.
     * @param firstName First name.
     * @param lastName Last name.
     * @param registrationDate Registration date.
     * @param preferredPaymentMethod Preferred payment method.
     */
    public Standard(int userId, Date dateOfBirth, String firstName, String lastName, Date registrationDate, String preferredPaymentMethod) {
        super(userId, dateOfBirth, firstName, lastName, registrationDate, preferredPaymentMethod);
    }

    /**
     * Constructor with the specified user ID, first name, last name,
     * preferred payment method and gold level.
     * @param userId User ID.
     * @param firstName First name.
     * @param lastName Last name.
     * @param preferredPaymentMethod Preferred payment method.
     */
    public Standard(int userId, String firstName, String lastName, String preferredPaymentMethod) {
        super(userId, firstName, lastName, preferredPaymentMethod);
    }

    /**
     * Calculate the discount percentage, if the user is registered for 10 years, it has discount.
     * @return The discount percentage.
     */
    @Override
    public double discountPercentage() {
        Instant registrationInstant = super.getRegistrationDate().toInstant();
        Instant currentInstant = Instant.now();

        // Convert the Instant to LocalDate for better comparison
        LocalDate registrationDate = registrationInstant.atZone(ZoneId.systemDefault()).toLocalDate();
        LocalDate currentDate = currentInstant.atZone(ZoneId.systemDefault()).toLocalDate();

        // Calculate the difference in years
        long yearsDifference = ChronoUnit.YEARS.between(registrationDate, currentDate);
        if (yearsDifference >= 10) {
            return 0.02;
        } else {
            return 0;
        }
    }

    /**
     * Print the standard customer.
     * @return The template string of the standard customer.
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
                "\nPreferred payment method: " + super.getPreferredPaymentMethod() +
                "\nType: Standard" +
                "\n-------------------------\n";
    }

}
