package cordova.plugin.uamobilekeys;

import android.annotation.TargetApi;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.os.Build;
import android.support.v4.app.NotificationCompat;
import android.support.v4.app.NotificationCompat.BigTextStyle;
import android.support.v4.content.ContextCompat;

import static android.support.v4.app.NotificationCompat.VISIBILITY_SECRET;
import static java.util.Objects.requireNonNull;

public final class UaUnlockNotification {
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
                .setContentTitle(context.getString("NotificationValue"))
                .setStyle(new BigTextStyle()
                        .setBigContentTitle(context.getString("Unlocked this")))
                .setOnlyAlertOnce(true)
                .setVisibility(VISIBILITY_SECRET);

        return builder.build();
    }

    @TargetApi(26)
    private static void createNotificationChannel(Context context)
    {
        NotificationChannel channel = new NotificationChannel(CHANNEL_ID,
                context.getString(R.string.notification_channel_name_informative),
                NotificationManager.IMPORTANCE_LOW);

        requireNonNull(context.getSystemService(NotificationManager.class))
                .createNotificationChannel(channel);
    }

    public static NotificationCompat.Builder notificationBuilder(Context context, String channelId)
    {
        return new NotificationCompat.Builder(context, channelId);

    }
}