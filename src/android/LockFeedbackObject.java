public class LockFeedbackObject {
    String DoorId;
    String DidUnlock;
    String BatteryStatus;

    public String getDoorId() {
        return DoorId;
    }

    public void setDoorId(String doorId) {
        this.DoorId = doorId;
    }

    public String getDidUnlock() {
        return this.DidUnlock;
    }

    public void setDidUnlock(String didUnlock) {
        this.DidUnlock = didUnlock;
    }

    public String getBatteryStatus() {
        return this.BatteryStatus;
    }

    public void setBatteryStatus(String batteryStatus) {
        this.BatteryStatus = batteryStatus;
    }
}
