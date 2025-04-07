package dataviewer3;

import java.awt.Color;

public class DataUtil {

    public static Integer parseMonth(String dateString) {
        Integer ret = null;
        if (dateString.indexOf("/") != -1) {
            String[] parts = dateString.split("/");
            if (parts.length == 3) {
                ret = Integer.parseInt(parts[0]);
            }
        } else if (dateString.indexOf("-") != -1) {
            String[] parts = dateString.split("-");
            if (parts.length == 3) {
                ret = Integer.parseInt(parts[1]);
            }
        } else {
            throw new RuntimeException(String.format("Unexpected date delimiter: '%s'", dateString));
        }
        if (ret == null || ret.intValue() < 1 || ret.intValue() > 12) {
            Debugger.trace("Unable to parse month from date: '%s'", dateString);
            return null;
        }
        return ret;
    }

    public static Integer parseYear(String dateString) {
        Integer ret = null;
        if (dateString.indexOf("/") != -1) {
            String[] parts = dateString.split("/");
            if (parts.length == 3) {
                ret = Integer.parseInt(parts[2]);
            }
        } else if (dateString.indexOf("-") != -1) {
            String[] parts = dateString.split("-");
            if (parts.length == 3) {
                ret = Integer.parseInt(parts[0]);
            }
        } else {
            throw new RuntimeException(String.format("Unexpected date delimiter: '%s'", dateString));
        }
        if (ret == null) {
            Debugger.trace("Unable to parse year from date: '%s'", dateString);
        }
        return ret;
    }

    public static Color getDataColor(Double value, boolean doGrayscale) {
        if (null == value) {
            return null;
        }
        double pct = (value - Constants.TEMPERATURE_MIN_C) / Constants.TEMPERATURE_RANGE;
        Debugger.trace("converted %f raw value to %f %%", value, pct);

        if (pct > 1.0) {
            pct = 1.0;
        } else if (pct < 0.0) {
            pct = 0.0;
        }
        int r, g, b;
        if (!doGrayscale) {
            r = (int) (255.0 * pct);
            g = 0;
            b = (int) (255.0 * (1.0 - pct));
        } else {
            r = g = b = (int) (255.0 * pct);
        }
        Debugger.trace("converting %f to [%d, %d, %d]", value, r, g, b);
        return new Color(r, g, b);
    }
}
