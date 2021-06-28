public enum ReaderBatteryStatus {
    Good (0x00),
    Warning (0x01),
    Critical (0x02),
    NotApplicable (-1);

    private final int value;
    private ReaderBatteryStatus(int value) {
        this.value = value;
    }

    public static ReaderBatteryStatus fromInt(int id) {
        ReaderBatteryStatus foundValue = NotApplicable;
        for (ReaderBatteryStatus type : ReaderBatteryStatus.values()) {
            if (type.value == id ) {
                foundValue = type;
                break;
            }
        }
        return foundValue;
    }
}