package dataviewer3;

public class Constants {
    // Private constants (alphabetical)
    public final static double DATA_WINDOW_BORDER = 50.0;
    public final static String DEFAULT_COUNTRY = "United States";
    public final static boolean DO_DEBUG = true;
    public final static boolean DO_TRACE = false;
    public final static double EXTREMA_PCT = 0.1;
    public final static int FILE_COUNTRY_IDX = 4;
    public final static int FILE_DATE_IDX = 0;
    public final static int FILE_NUM_COLUMNS = 5;
    public final static int FILE_STATE_IDX = 3;
    public final static int FILE_TEMPERATURE_IDX = 1;
    public final static int FILE_UNCERTAINTY_IDX = 2;
    public final static int GUI_MODE_MAIN_MENU = 0;
    public final static int GUI_MODE_DATA = 1;
    public final static double MENU_STARTING_X = 40.0;
    public final static double MENU_STARTING_Y = 90.0;
    public final static double MENU_ITEM_SPACING = 5.0;
    public final static String[] MONTH_NAMES = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    public final static int RECORD_MONTH_IDX = 1;
    public final static int RECORD_STATE_IDX = 3;
    public final static int RECORD_TEMPERATURE_IDX = 2;
    public final static int RECORD_YEAR_IDX = 0;
    public final static double TEMPERATURE_MAX_C = 30.0;
    public final static double TEMPERATURE_MIN_C = -10.0;
    public final static double TEMPERATURE_RANGE = TEMPERATURE_MAX_C - TEMPERATURE_MIN_C;
    public final static VisState[] VISUALIZATION_MODES = { new RawVisState(), new ExtremaVisState() };
    public final static int VISUALIZATION_RAW_IDX = 0;
    public final static int VISUALIZATION_EXTREMA_IDX = 1;
    public final static int WINDOW_HEIGHT = 720;
    public final static String WINDOW_TITLE = "DataViewer Application";
    public final static int WINDOW_WIDTH = 1320;
}
