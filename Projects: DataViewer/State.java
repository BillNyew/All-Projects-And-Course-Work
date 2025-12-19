package dataviewer3;

import java.util.ArrayList;
import java.util.List;
import java.util.SortedSet;
import java.util.TreeSet;

public class State {
    private String name;
    private List<DataRecord> dataRecords;
    private SortedSet<Integer> years;


    public State(String name) {
        this.name = name;
        this.dataRecords = new ArrayList<>();
        this.years = new TreeSet<Integer>();
    }

    public String getName() {
        return name;
    }

    public List<DataRecord> getDataRecords() {
        return dataRecords;
    }

    public void addDataRecord(DataRecord dataRecord) {
        dataRecords.add(dataRecord);
    }
   
	public SortedSet<Integer> getYears() {
		
		for (int i = 0; i < dataRecords.size(); i++) {
			int temp_year = dataRecords.get(i).getYear();
			years.add(temp_year);
    	}
		return years;
	}

	@Override
	public String toString() {
		return name;
	}

}
