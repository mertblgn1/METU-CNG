import java.util.Date;

/**
 * The Host class represents a host. This class stores information about hosts, including host ID,
 * first name, last name, and the registration date of the host.
 */
public class Host {
    private int hostId;
    private String firstName;
    private String lastName;
    private Date registrationDate;

    /** Constructor with the specified hostId, firstName, lastName and registration date
     */
    public Host(int hostId, String firstName, String lastName, Date registrationDate) {
        this.hostId = hostId;
        this.firstName = firstName;
        this.lastName = lastName;
        this.registrationDate = registrationDate;
    }

    /** Constructor with the specified hostId, firstName, lastName. Registration date is
     * the day instance is created by default.
     */
    public Host(int hostId, String firstName, String lastName) {
        this.hostId = hostId;
        this.firstName = firstName;
        this.lastName = lastName;
        registrationDate = new Date();
    }

    /** Default constructor
     */
    public Host() {
    }

    /** Return hostId
     */
    public int getHostId() {
        return hostId;
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

    /** Return registration date
     */
    public Date getRegistrationDate() {
        return registrationDate;
    }

    /** Set hostId
     */
    public void setHostId(int hostId) {
        this.hostId = hostId;
    }

    /** Set firstName
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /** Set lastName
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    /** Set registration date
     */
    public void setRegistrationDate(Date registrationDate) {
        this.registrationDate = registrationDate;
    }
}
