import java.util.ArrayList;
import java.util.Date;

/**
 * The PopulateData class initialize and populate data for the whole program.
 * It creates instances of users, properties, hosts, and bookings,
 * and adds them to their respective lists.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 */
public class PopulateData {
    public ArrayList<User> users = new ArrayList<User>();
    public ArrayList<Property> properties = new ArrayList<Property>();
    public ArrayList<Booking> bookings = new ArrayList<Booking>();

    public PopulateData() {
        // Create the user1 as a Gold customer
        Gold user1 = new Gold(1, new Date("01/01/1981"), "Yeliz", "Yesilada", new Date("01/01/2023"), "Cash", 3);
        // Create the user2 as a Standard customer
        Standard user2 = new Standard(2, new Date("02/02/1982"), "Enver", "Ever", new Date("02/02/2000"), "Credit Card");
        // Create the user3 as a Host
        Host user3 = new Host(3, new Date("03/03/1983"), "Sukru", "Eraslan", new Date("03/03/2023"), 123);

        // Create the property1 as a shared property
        SharedProperty property1 = new SharedProperty(1, 3, 5, "Kyrenia", 100, new Date("03/04/2023"), "It was in good condition");
        // Create the property2 as a full property
        FullProperty property2 = new FullProperty(2, 4, 6, "Nicosia", 200, new Date("04/05/2023"), "Broken toilet that needs to be fixed", 200);
        // Create the property3 as a full property
        FullProperty property3 = new FullProperty(3, 2, 3, "Famagusta", 150, new Date("05/06/2023"), "It was noisy.", 110);

        // Create the booking1
        Booking booking1 = new Booking(new Date("10/01/2023"), new Date("10/04/2023"), false, property1);
        Booking booking4 = new Booking(new Date("10/01/2022"), new Date("11/04/2022"), false, property1);
        Booking booking2 = new Booking(new Date("09/02/2023"), new Date("09/07/2023"), false, property2);
        Booking booking3 = new Booking(new Date("08/08/2023"), new Date("08/15/2023"), false, property3);

        // Assign the bookings to users
        user1.addBooking(booking1);
        user1.addBooking(booking4);
        user2.addBooking(booking2);
        user2.addBooking(booking3);

        // Add users to the users list
        users.add(user1);
        users.add(user2);
        users.add(user3);

        // Assign the hosts to the properties
        property1.setBelongsTo(user3);
        property2.setBelongsTo(user3);
        property3.setBelongsTo(user3);

        // Add properties to the properties list
        properties.add(property1);
        properties.add(property2);
        properties.add(property3);

        // Add bookings to the bookings list
        bookings.add(booking1);
        bookings.add(booking2);
        bookings.add(booking3);
    }

    /**
     * Constructor with the specified parameters.
     *
     * @param users User list.
     * @param properties Property list.
     * @param bookings Booking list.
     */
    public PopulateData(ArrayList<User> users, ArrayList<Property> properties, ArrayList<Booking> bookings) {
        this.users = users;
        this.properties = properties;
        this.bookings = bookings;
    }

    /**
     * Constructor with the specified parameters.
     *
     * @param users User list.
     * @param properties Property list.
     */
    public PopulateData(ArrayList<User> users, ArrayList<Property> properties) {
        this.users = users;
        this.properties = properties;
    }
}
