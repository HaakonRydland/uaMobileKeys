package cordova.plugin.uamobilekeys;

import android.annotation.TargetApi;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.content.res.Resources;
import android.os.Build;
import android.support.v4.app.NotificationCompat;
import android.support.v4.app.NotificationCompat.BigTextStyle;
import android.support.v4.content.ContextCompat;


import static android.support.v4.app.NotificationCompat.VISIBILITY_SECRET;
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
                .setContentTitle("Mobile Access is running")
                .setStyle(new BigTextStyle()
                        .setBigContentTitle("Mobile Access is running"))
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
        //Resources r = context.getResources();
        //int drawableId = r.getIdentifier("ic_stat_vpn_key", "drawable", "cordova.plugin.uamobilekeys");

        return new NotificationCompat.Builder(context, channelId)
                .setColor(context.getResources().getColor("#FF5722"))
                .setSmallIcon(android.R.drawable.ic_dialog_info);
    }
}
