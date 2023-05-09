#ifndef RPMMETER_H
#define RPMMETER_H

#include <QWidget>
#include <QPainter>

class RPMMeter : public QWidget
{
    Q_OBJECT
public:
    explicit RPMMeter(QWidget *parent = nullptr);
    ~RPMMeter();

    void paintEvent(QPaintEvent *event) override;

    void draw_speed_arc(QPainter *painter, QPen *pen, QBrush *brush, QRectF *rectF, qreal current_angle, qreal speed_progress_child_arc_length, qreal speed_progress_child_split_length, qreal speed_progress_arc_view_max_radius);

    void draw_dynamic_speed_text(QPainter *painter, QPen *pen, QBrush *brush, qreal value);
    void draw_fuel_arc(QPainter *painter, QRectF *rectF, QPen *pen, QBrush *brush,qreal current_angle,qreal fuelProgressArcViewMaxRadius, qreal fuelProgressArcViewStartAngle, qreal fuelProgressArcViewEndAngle,qreal fuelProgressChildArcLength);
    void draw_dynamic_speed_measurement_unit_text(QPainter *painter, QPen *pen, QBrush *brush);

};

#endif // RPMMETER_H
