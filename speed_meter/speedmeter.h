#ifndef SPEEDMETER_H
#define SPEEDMETER_H

#include <QWidget>
#include <QPainter>

class SpeedMeter : public QWidget
{
    Q_OBJECT

public:
    explicit SpeedMeter(QWidget *parent = nullptr);
    ~SpeedMeter();

    void paintEvent(QPaintEvent *event) override;

    void draw_speed_arc(QPainter *painter, QPen *pen, QBrush *brush, QRectF *rectF, qreal current_angle, qreal speed_progress_child_arc_length, qreal speed_progress_child_split_length, qreal speed_progress_arc_view_max_radius);

    void draw_dynamic_speed_text(QPainter *painter, QPen *pen, QBrush *brush, qreal value);
    void draw_fuel_arc(QPainter *painter, QRectF *rectF, QPen *pen, QBrush *brush,qreal current_angle,qreal fuelProgressArcViewMaxRadius, qreal fuelProgressArcViewStartAngle, qreal fuelProgressArcViewEndAngle,qreal fuelProgressChildArcLength);
    void draw_dynamic_speed_measurement_unit_text(QPainter *painter, QPen *pen, QBrush *brush);
};

#endif // SPEEDMETER_H
