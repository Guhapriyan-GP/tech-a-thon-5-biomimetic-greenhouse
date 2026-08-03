#include <math.h>

// Variables for MPU6050 readings
float accel_x, accel_y, accel_z;
float gyro_x, gyro_y, gyro_z;
float theta_filtered = 0.0f;
const float alpha = 0.98f;

// Calculate pitch angle from accelerometer (Gravity-referenced)
float calculate_accel_pitch(float ax, float ay, float az) {
    return atan2f(ax, sqrtf(ay * ay + az * az)) * (180.0f / M_PI);
}

// Complementary filter to confirm physical vent angle
float update_vent_angle(float dt) {
    float theta_accel = calculate_accel_pitch(accel_x, accel_y, accel_z);
    
    // Fuse gyroscope transient data with accelerometer baseline
    theta_filtered = alpha * (theta_filtered + gyro_x * dt) + (1.0f - alpha) * theta_accel;
    
    return theta_filtered;
}

// Wind force detection logic to maximize natural draft
bool detect_wind_gust(float gyro_threshold) {
    // Spikes in angular rate uncorrelated with stepper motor commands indicate wind
    if (fabs(gyro_y) > gyro_threshold) {
        return true; 
    }
    return false;
}