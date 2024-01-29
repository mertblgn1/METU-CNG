import java.util.ArrayList;
import java.util.Date;

/**
 * The PopulateData class initialize and populate data for the whole program.
 * It creates instances of users, properties, hosts, and bookings,
 * and adds them to their respective lists.
 */
public class PopulateData {
    public ArrayList<User> users = new ArrayList<>();
    public ArrayList<Property> properties = new ArrayList<>();
    public ArrayList<Booking> bookings = new ArrayList<>();
    public ArrayList<Host> hosts = new ArrayList<>();

    /** Customized default constructor.
     */
    public PopulateData() {
        // Create 3 users
        User user1 = new User(0, new Date("01/01/1980"),"Yeliz", "Yesilada");
        User user2 = new User(1, new Date("01/01/1975"),"Enver", "Ever");
        User user3 = new User(2, new Date("01/01/1979"),"Sukru", "Eraslan");

        // Create 3 properties
        Property property1 = new Property(0, 1, 2, "Nicosia", 50, 0);
        Property property2 = new Property(1, 2, 3, "Kyrenia", 100, 1);
        Property property3 = new Property(2, 3, 4, "Istanbul", 150, 2);

        // Create 3 hosts
        Host host1 = new Host(0, "Okan", "Topcu", new Date("01/01/2021"));
        Host host2 = new Host(1, "Okan", "Topcu", new Date("01/01/2022"));
        Host host3 = new Host(2, "Okan", "Topcu", new Date("01/01/2023"));

        // Create 3 bookings
        Booking booking1 = new Booking(new Date("10/01/2023"), new Date("10/04/2023"), property1);
        Booking booking2 = new Booking(new Date("09/02/2023"), new Date("09/07/2023"), property2);
        Booking booking3 = new Booking(new Date("08/08/2023"), new Date("08/15/2023"), property3);

        // Assign bookings to the users
        user1.addBooking(booking1);
        user2.addBooking(booking2);
        user3.addBooking(booking3);

        // Add users to the users list
        users.add(user1);
        users.add(user2);
        users.add(user3);

        // Add properties to the properties list
        properties.add(property1);
        properties.add(property2);
        properties.add(property3);

        // Add hosts to the hosts list
        hosts.add(host1);
        hosts.add(host2);
        hosts.add(host3);

        // Add bookings to the bookings list
        bookings.add(booking1);
        bookings.add(booking2);
        bookings.add(booking3);
    }

    /** Constructor with the specified users, properties, booking, hosts lists
     */
    public PopulateData(ArrayList<User> users, ArrayList<Property> properties, ArrayList<Booking> bookings, ArrayList<Host> hosts) {
        this.users = users;
        this.properties = properties;
        this.bookings = bookings;
        this.hosts = hosts;
    }

    /** Constructor with the specified users and properties lists
     */
    public PopulateData(ArrayList<User> users, ArrayList<Property> properties) {
        this.users = users;
        this.properties = properties;
    }
}
