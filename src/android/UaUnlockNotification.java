package cordova.plugin.uamobilekeys;

import android.annotation.TargetApi;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.content.res.Resources;
import android.os.Build;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationCompat.BigTextStyle;
import androidx.core.content.ContextCompat;


import static androidx.core.app.NotificationCompat.VISIBILITY_SECRET;
import static java.util.Objects.requireNonNull;

public final class UaUnlockNotification
{
    public static final String CHANNEL_ID = "unlock";

    private UaUnlockNotification()
    {
        // NOP
    }

    public static Notification create(Context context)
    {
        if (Build.VERSION.SDK_INT >= 26)
        {
            // 26 requires a notification channel for notifications to appear
            createNotificationChannel(context);
        }

        final NotificationCompat.Builder builder = notificationBuilder(context, CHANNEL_ID)
                .setContentTitle("Mobile access is running. Close the scan window to stop scanning.")
                .setStyle(new BigTextStyle()
                        .setBigContentTitle("Scanning for doors"))
                .setOnlyAlertOnce(true)
                .setVisibility(VISIBILITY_SECRET);

        return builder.build();
    }

    @TargetApi(26)
    private static void createNotificationChannel(Context context)
    {
        NotificationChannel channel = new NotificationChannel(CHANNEL_ID,
                "Running foreground scan service",
                NotificationManager.IMPORTANCE_LOW);

        requireNonNull(context.getSystemService(NotificationManager.class))
                .createNotificationChannel(channel);
    }

    public static NotificationCompat.Builder notificationBuilder(Context context, String channelId)
    {
        return new NotificationCompat.Builder(context, channelId)
                .setSmallIcon(android.R.drawable.ic_dialog_info);
    }
}
