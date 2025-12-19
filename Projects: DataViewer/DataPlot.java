	package dataviewer3;

import java.awt.Color;
import java.util.List;
import java.util.SortedMap;
import java.util.TreeMap;

import edu.du.dudraw.Draw;

public class DataPlot {
	private Draw m_window;
    private TreeMap<Integer, SortedMap<Integer, Double>> m_plotData;
    private TreeMap<Integer, Double> m_plotMonthlyMaxValue;
    private TreeMap<Integer, Double> m_plotMonthlyMinValue;
	
    
    public DataPlot(Draw window) {
		m_window = window;

}

	public void updatePlotData(State selectedState, Integer selectedStartYear, Integer selectedEndYear) {

		System.out.println(selectedState);
		System.out.println(selectedStartYear);
		System.out.println(selectedEndYear);
		
		
		m_plotData = new TreeMap<Integer,SortedMap<Integer,Double>>();
		for(int month = 1; month <= 12; month++) {
			// any year/months not filled in will be null
			m_plotData.put(month, new TreeMap<Integer,Double>());
		}
		// now run through the raw data and if it is related to the current state and within the current
		// years, put it in a sorted data structure, so that we 
		// find min/max year based on data 
		m_plotMonthlyMaxValue = new TreeMap<Integer,Double>();
		m_plotMonthlyMinValue = new TreeMap<Integer,Double>();
		// initialize
		for(int i = 1; i <= 12; i++) {
			m_plotMonthlyMaxValue.put(i, Double.MIN_VALUE);
			m_plotMonthlyMinValue.put(i, Double.MAX_VALUE);
		}

		List<DataRecord> stateRecords = selectedState.getDataRecords();
		for (int i = 0; i < stateRecords.size(); i++) {
			Integer year = stateRecords.get(i).getYear();
			
			// Check to see if they are the state and year range we care about
			if (year.compareTo(selectedStartYear) >= 0 && year.compareTo(selectedEndYear) <= 0) {
						
				// Ok, we need to add this to the list of values for the month
				Integer month = stateRecords.get(i).getMonth();
				Double value = stateRecords.get(i).getTemperature();
				
				if(!m_plotMonthlyMinValue.containsKey(month) || value.compareTo(m_plotMonthlyMinValue.get(month)) < 0) {
					m_plotMonthlyMinValue.put(month, value);
				}
				if(!m_plotMonthlyMaxValue.containsKey(month) || value.compareTo(m_plotMonthlyMaxValue.get(month)) > 0) {
					m_plotMonthlyMaxValue.put(month, value);
				}
	
				m_plotData.get(month).put(year, value);
			}
		}
		Debugger.debug("plot data: %s", m_plotData.toString());
	}
  
	 public void drawData(Country selectedCountry, State selectedState, Integer selectedStartYear, Integer selectedEndYear, VisState visState) {
	    	// Give a buffer around the plot window
	        m_window.setXscale(-Constants.DATA_WINDOW_BORDER, Constants.WINDOW_WIDTH+Constants.DATA_WINDOW_BORDER);
			m_window.setYscale(-Constants.DATA_WINDOW_BORDER, Constants.WINDOW_HEIGHT+Constants.DATA_WINDOW_BORDER);

	    	// gray background
	    	m_window.clear(Color.LIGHT_GRAY);

	    	// white plot area
			m_window.setPenColor(Color.WHITE);
			m_window.filledRectangle(Constants.WINDOW_WIDTH/2.0, Constants.WINDOW_HEIGHT/2.0, Constants.WINDOW_WIDTH/2.0, Constants.WINDOW_HEIGHT/2.0);  

	    	m_window.setPenColor(Color.BLACK);
	    	
	    	double nCols = 12; // one for each month
	    	double nRows = selectedEndYear - selectedStartYear + 1; // for the years
	    	
	    	Debugger.debug("nCols = %f, nRows = %f", nCols, nRows);
	 		
	        double cellWidth = Constants.WINDOW_WIDTH / nCols;
	        double cellHeight = Constants.WINDOW_HEIGHT / nRows;
	        
	        Debugger.debug("cellWidth = %f, cellHeight = %f", cellWidth, cellHeight);
	        
	        boolean extremaVisualization = !visState.isRaw();
	        Debugger.info("visualization: %s (extrema == %b)", visState, extremaVisualization);
	        
	        for(int month = 1; month <= 12; month++) {
	            double fullRange = m_plotMonthlyMaxValue.get(month) - m_plotMonthlyMinValue.get(month);
	            double extremaMinBound = m_plotMonthlyMinValue.get(month) + Constants.EXTREMA_PCT * fullRange;
	            double extremaMaxBound = m_plotMonthlyMaxValue.get(month) - Constants.EXTREMA_PCT * fullRange;


	            // draw the line separating the months and the month label
	        	m_window.setPenColor(Color.BLACK);
	        	double lineX = (month-1.0)*cellWidth;
	        	m_window.line(lineX, 0.0, lineX, Constants.WINDOW_HEIGHT);
	        	m_window.text(lineX+cellWidth/2.0, -Constants.DATA_WINDOW_BORDER/2.0, Constants.MONTH_NAMES[month]);
	        	
	        	// there should always be a map for the month
	        	SortedMap<Integer,Double> monthData = m_plotData.get(month);
	        	
	        	for(int year = selectedStartYear; year <= selectedEndYear; year++) {

	        		// month data structure might not have every year
	        		if(monthData.containsKey(year)) {
	        			Double value = monthData.get(year);
	        			
	        			double x = (month-1.0)*cellWidth + 0.5 * cellWidth;
	        			double y = (year-selectedStartYear)*cellHeight + 0.5 * cellHeight;
	        			
	        			Color cellColor = null;
	        			
	        			// get either color or grayscale depending on visualization mode
	        			if(extremaVisualization && value > extremaMinBound && value < extremaMaxBound) {
	        				cellColor = DataUtil.getDataColor(value, true);
	        			}
	        			else if(extremaVisualization) {
	        				// doing extrema visualization, show "high" values in red "low" values in blue.
	        				if(value >= extremaMaxBound) {
	        					cellColor = Color.RED;
	        				}
	        				else {
	        					cellColor = Color.BLUE;
	        				}
	        			}
	        			else {
	        				cellColor = DataUtil.getDataColor(value, false);
	        			}
	        			
	        			// draw the rectangle for this data point
	        			m_window.setPenColor(cellColor);
	        			Debugger.trace("month = %d, year = %d -> (%f, %f) with %s", month, year, x, y, cellColor.toString());
	        			m_window.filledRectangle(x, y, cellWidth/2.0, cellHeight/2.0);
	        		}
	        	}
	        }
	        
	        // draw the labels for the y-axis
	        m_window.setPenColor(Color.BLACK);

	        double labelYearSpacing = (selectedEndYear - selectedStartYear) / 5.0;
	        double labelYSpacing = Constants.WINDOW_HEIGHT/5.0;
	        // spaced out by 5, but need both the first and last label, so iterate 6
	        for(int i=0; i<6; i++) {
	        	int year = (int)Math.round(i * labelYearSpacing + selectedStartYear);
	        	String text = String.format("%4d", year);
	        	
	        	m_window.textRight(0.0, i*labelYSpacing, text);
	        	m_window.textLeft(Constants.WINDOW_WIDTH, i*labelYSpacing, text);
	        }
	     
	        // draw rectangle around the whole data plot window
	        m_window.rectangle(Constants.WINDOW_WIDTH/2.0, Constants.WINDOW_HEIGHT/2.0, Constants.WINDOW_WIDTH/2.0, Constants.WINDOW_HEIGHT/2.0);
	        
	        // put in the title
	        String title = String.format("%s, %s from %d to %d. Press 'M' for Main Menu.  Press 'Q' to Quit.",
	        		selectedState, selectedCountry, selectedStartYear, selectedEndYear);
	        m_window.text(Constants.WINDOW_WIDTH/2.0, Constants.WINDOW_HEIGHT+Constants.DATA_WINDOW_BORDER/2.0, title);
		}
}

