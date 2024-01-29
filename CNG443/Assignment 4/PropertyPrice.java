/**
 * This interface represents a property with the ability to calculate its price per day.
 * Classes implementing this interface must provide an implementation for the 'calculatePricePerDay' method.
 */
public interface PropertyPrice {
    /**
     * Calculates the price per day for the property.
     * The actual implementation of this method should define how the price is calculated based on the specific property type.
     *
     * @return The calculated price per day for the property.
     */
    double calculatePricePerDay();
}
