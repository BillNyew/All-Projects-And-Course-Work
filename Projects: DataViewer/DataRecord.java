package dataviewer3;

public class DataRecord {
    private int year;
    private int month;
    private double temperature;

    public DataRecord(int year, int month, double temperature) {
        this.year = year;
        this.month = month;
        this.temperature = temperature;
    }

    public int getYear() {
        return year;
    }

    public int getMonth() {
        return month;
    }

    public double getTemperature() {
        return temperature;
    }

	@Override
	public String toString() {
		return year + " " + month + " " + temperature;
	}

}
