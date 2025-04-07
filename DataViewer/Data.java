package dataviewer3;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Data {

	private ArrayList<Country> m_dataCountries;
	
	
	public Data() {
	    m_dataCountries = new ArrayList<Country>();

	}
	
	public ArrayList<Country> getDataCountries() {
		return m_dataCountries;
	}


	public void loadData(String m_dataFile) throws FileNotFoundException {
	    
    	try (Scanner scanner = new Scanner(new File(m_dataFile))) {
    	    boolean skipFirst = true;
    	    while (scanner.hasNextLine()) {
    	    	String line = scanner.nextLine();
    	    	
    	    	if(!skipFirst) {
    	    		this.addRecordFromLine(line);
    	    	}
    	    	else {
    	    		skipFirst = false;
    	    	}
    	    }
    	}
    }
	
	private void addRecordFromLine(String line) {
        List<String> rawValues = new ArrayList<String>();
        try (Scanner rowScanner = new Scanner(line)) {
            rowScanner.useDelimiter(",");
            while (rowScanner.hasNext()) {
                rawValues.add(rowScanner.next());
            }
        }

        try {
        	Integer year = DataUtil.parseYear(rawValues.get(Constants.FILE_DATE_IDX));
        	Integer month = DataUtil.parseMonth(rawValues.get(Constants.FILE_DATE_IDX));
        	double temp = Double.parseDouble(rawValues.get(Constants.FILE_TEMPERATURE_IDX));
        	String state = rawValues.get(Constants.FILE_STATE_IDX);
        	String country = rawValues.get(Constants.FILE_COUNTRY_IDX);
        	DataRecord dataInfo = new DataRecord((int)year, (int)month, temp);

        	boolean found_country = false;
        	for (int i = 0; i < m_dataCountries.size(); i++) {
        		Country temp_country = m_dataCountries.get(i);
        		
        		if (temp_country.getName().equals(country)) {
        			found_country = true;
        			boolean added_info = false;
        			for (int j = 0; j < m_dataCountries.get(i).getStates().size(); j++) {
        				State temp_state=temp_country.getStates().get(j);
       
                		if (temp_state.getName().equals(state)) {
                			temp_state.addDataRecord(dataInfo);  
                			added_info = true;
                		}
                	}
        			if (!added_info) {
        			State new_state = new State(state);
        			new_state.addDataRecord(dataInfo);
        			temp_country.addState(new_state);
        			}
        			
        		}
        		
        	}
        	if (!found_country) {
        		Country new_country = new Country(country);
        		State new_state = new State(state);
    			new_state.addDataRecord(dataInfo);
    			new_country.addState(new_state);
    			m_dataCountries.add(new_country);
        	}
        }
        catch(NumberFormatException e) {
        	Debugger.trace("unable to parse data line, skipping...'%s'", line);
        	
        }
    }
}
