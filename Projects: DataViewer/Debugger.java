package dataviewer3;

public class Debugger {

    public static void trace(String format, Object... args) {
        if (Constants.DO_TRACE) {
            System.out.print("TRACE: ");
            System.out.println(String.format(format, args));
        }
    }

    public static void info(String format, Object... args) {
        System.out.print("INFO: ");
        System.out.println(String.format(format, args));
    }

    public static void error(String format, Object... args) {
        System.out.print("ERROR: ");
        System.out.println(String.format(format, args));
    }

    public static void debug(String format, Object... args) {
        if (Constants.DO_DEBUG) {
            System.out.print("DEBUG: ");
            System.out.println(String.format(format, args));
        }
    }
}
