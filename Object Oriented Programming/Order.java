package class7_1;


interface OrderState {
    void viewStatus();
    OrderState shipOrder() throws OrderException;
    OrderState deliverOrder() throws OrderException;
}

class ProccesedState implements OrderState {
    private Order order;

    public void ProcessedState(Order order) {
        this.order = order;
    }

    @Override
    public void viewStatus() {
        System.out.println("Processing order " + order.getOrderNumber());
    }

    @Override
    public OrderState shipOrder() throws OrderException {
        System.out.println("Shipped!");
        return new ShippedState(order);
    }

    @Override
    public OrderState deliverOrder() throws OrderException {
        throw new OrderException("Order has not shipped yet");
    }
}

class ShippedState implements OrderState {
    private Order order;

    public ShippedState(Order order) {
        this.order = order;
    }

    @Override
    public void viewStatus() {
        System.out.println("Shipping order " + order.getOrderNumber());
    }

    @Override
    public OrderState shipOrder() throws OrderException {
        throw new OrderException("Order has already shipped");
    }

    @Override
    public OrderState deliverOrder() throws OrderException {
        System.out.println("Delivered!");
        return new DeliveredState(order);
    }
}

class DeliveredState implements OrderState {
    private Order order;

    public DeliveredState(Order order) {
        this.order = order;
    }

    @Override
    public void viewStatus() {
        System.out.println("Delivered order " + order.getOrderNumber());
    }

    @Override
    public OrderState shipOrder() throws OrderException {
        throw new OrderException("Order has already been delivered");
    }

    @Override
    public OrderState deliverOrder() throws OrderException {
        throw new OrderException("Order has already been delivered");
    }
}

public class Order {
    private int orderNumber;
    private OrderState state; 

    public Order(int orderNumber) {
        this.orderNumber = orderNumber;
        this.state = new ProcessedState(this);
    }

    public void viewStatus() {
        state.viewStatus();
    }

    public void shipOrder() throws OrderException {
        state = state.shipOrder(); 
    }

    public void deliverOrder() throws OrderException {
        state = state.deliverOrder(); 
    }

    public int getOrderNumber() {
        return orderNumber;
    }
}