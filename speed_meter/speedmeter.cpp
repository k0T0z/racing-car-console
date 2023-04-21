#include "speedmeter.h"

SpeedMeter::SpeedMeter(QWidget *parent)
    : QWidget(parent) {};

SpeedMeter::~SpeedMeter() {};

void SpeedMeter::paintEvent(QPaintEvent *event)
{
    qreal value {0.6};

    QPainter *painter { new QPainter(this)};

    QPen *pen { new QPen()};
    QBrush *brush { new QBrush(Qt::black)}; // TODO: remove this black and fix
    painter->setRenderHint(QPainter::Antialiasing);

    QPointF center { painter->window().center()};

    qreal width {static_cast<qreal>(painter->window().width())};
    qreal height { static_cast<qreal>(painter->window().height())};

    qreal speed_progress_arc_view_max_radius {fmin(width, height) * 0.42 };

    qreal speed_progress_arc_view_start_angle {240.0};
    qreal speed_progress_arc_view_end_angle  {10.0};

    qreal speed_progress_parent_arc_length {
        speed_progress_arc_view_start_angle -
                speed_progress_arc_view_end_angle
    };

    qreal speed_progress_child_arc_length { speed_progress_parent_arc_length / 12.0};

    qreal current_angle {speed_progress_arc_view_start_angle};

    qreal speed_progress_child_split_length {
        speed_progress_parent_arc_length * 0.135
    };

    QRectF *rectF = new QRectF(center.x() - speed_progress_arc_view_max_radius, center.y() - speed_progress_arc_view_max_radius, 2 * speed_progress_arc_view_max_radius, 2 * speed_progress_arc_view_max_radius);

    draw_speed_arc(painter,pen,brush, rectF, current_angle, speed_progress_child_arc_length, speed_progress_child_split_length, speed_progress_arc_view_max_radius);

    pen->setColor(Qt::red);
    painter->setPen(*pen);
    brush->setColor(Qt::transparent);
    painter->setBrush(*brush);
    painter->drawArc(*rectF, speed_progress_arc_view_start_angle * 16, (-1 * speed_progress_parent_arc_length * value) * 16);

    /*
        This is the black circle behind value of current speed.
    */
    pen->setColor(Qt::transparent);
    painter->setPen(*pen);
    brush->setColor(Qt::black);
    painter->setBrush(*brush);
    painter->drawEllipse(center,fmin(width, height) * 0.25, fmin(width, height) * 0.25);

    draw_dynamic_speed_text(painter,pen,brush, 0.6);

    draw_dynamic_speed_measurement_unit_text(painter,pen,brush);

    qreal fuel_progress_arc_view_max_radius {
        fmin(width, height) * 0.45
    };

    qreal fuel_progress_arc_view_start_angle  {300.0};
    qreal fuel_progress_arc_view_end_angle  {350.0};

    qreal fuel_progress_arc_length {
        fuel_progress_arc_view_end_angle - fuel_progress_arc_view_start_angle
    };

    qreal fuel_progress_child_arc_length { fuel_progress_arc_length * 0.5};

    current_angle = fuel_progress_arc_view_start_angle;

    rectF->setRect(center.x() - fuel_progress_arc_view_max_radius, center.y() - fuel_progress_arc_view_max_radius, 2 * fuel_progress_arc_view_max_radius, 2 * fuel_progress_arc_view_max_radius);

    draw_fuel_arc(painter,rectF, pen,brush,current_angle, fuel_progress_arc_view_max_radius, fuel_progress_arc_view_start_angle, fuel_progress_arc_length,fuel_progress_child_arc_length);

    fuel_progress_arc_view_max_radius -= fmin(width, height) * 0.025 * 0.5;
    rectF->setRect(center.x() - fuel_progress_arc_view_max_radius, center.y() - fuel_progress_arc_view_max_radius, 2 * fuel_progress_arc_view_max_radius, 2 * fuel_progress_arc_view_max_radius);
    pen->setColor("#FF99AAB5");
    pen->setWidthF(fmin(width, height) * 0.025);
    painter->setPen(*pen);
    brush->setColor(Qt::transparent);
    painter->setBrush(*brush);
    painter->drawArc(*rectF, fuel_progress_arc_view_start_angle * 16, (fuel_progress_arc_length * value) * 16);

    delete rectF;

    delete brush;
    delete pen;
    delete painter;
}

void SpeedMeter::draw_speed_arc(QPainter *painter, QPen *pen, QBrush *brush, QRectF *rectF, qreal current_angle, qreal speed_progress_child_arc_length, qreal speed_progress_child_split_length, qreal speed_progress_arc_view_max_radius) {
    QPointF center {painter->window().center()};

    qreal width {static_cast<qreal>(painter->window().width())};
    qreal height { static_cast<qreal>(painter->window().height())};

    QFont *static_speed_font {new QFont("Arial", fmin(width, height) * 0.04)};
    pen->setColor(Qt::black);
    pen->setWidthF(fmin(width, height) * 0.025);
    painter->setPen(*pen);
    brush->setColor(Qt::transparent);
    painter->setBrush(*brush);
    painter->setFont(*static_speed_font);

    for (int i = 0, current_speed = 0; i < 12; i++, current_speed += 20) {

        /*
         *
         *  current_angle starts from 240 degree till 10 degree
         *  (speed_progress_child_arc_length - speed_progress_child_split_length) is child length - split length which draws the arc splitted into 12 part.
         *
        */
        painter->drawArc(*rectF, current_angle * 16, (speed_progress_child_arc_length - speed_progress_child_split_length) * 16);

        QPointF *current_angle_text_position = new QPointF(
                             center.x() +
                                 (speed_progress_arc_view_max_radius -
                                         fmin(width, height) * 0.02) *
                                     cos(qDegreesToRadians(-1 * current_angle)),
                             center.y() +
                                 (speed_progress_arc_view_max_radius -
                                         fmin(width, height) * 0.02) *
                                     sin(qDegreesToRadians(-1 * current_angle))

                    );
        painter->drawText(*current_angle_text_position, std::to_string(current_speed).data());

        delete current_angle_text_position;

        current_angle -= speed_progress_child_arc_length;

        switch (i) {
                case 11:
                  current_speed += 20;
                  current_angle_text_position = new QPointF(
                                               center.x() +
                                                   (speed_progress_arc_view_max_radius -
                                                           fmin(width, height) * 0.02) *
                                                       cos(qDegreesToRadians(-1 * current_angle)),
                                               center.y() +
                                                   (speed_progress_arc_view_max_radius -
                                                           fmin(width, height) * 0.02) *
                                                       sin(qDegreesToRadians(-1 * current_angle))

                                      );
                  painter->drawText(*current_angle_text_position, std::to_string(current_speed).data());
                  delete current_angle_text_position;
                  break;
                default:
                  break;
              }
    }

    delete static_speed_font;
}

void SpeedMeter::draw_fuel_arc(QPainter *painter, QRectF *rectF, QPen *pen, QBrush *brush,qreal current_angle,qreal fuel_progress_arc_view_max_radius, qreal fuel_progress_arc_view_start_angle, qreal fuel_progress_arc_length ,qreal fuel_progress_child_arc_length) {
    QPointF center { painter->window().center()};

    qreal width {static_cast<qreal>(painter->window().width())};
    qreal height { static_cast<qreal>(painter->window().height())};

    pen->setColor("#FF99AAB5");
    pen->setWidthF(fmin(width, height) * 0.004);
    painter->setPen(*pen);
    brush->setColor(Qt::transparent);
    painter->setBrush(*brush);

    painter->drawArc(*rectF, fuel_progress_arc_view_start_angle * 16, (fuel_progress_arc_length ) * 16);

    for (int i = 0; i < 3; i++) {

          painter->drawLine(QPointF(
                                center.x() +
                                    (fuel_progress_arc_view_max_radius) * cos(qDegreesToRadians(-1 * current_angle)),
                                center.y() +
                                    (fuel_progress_arc_view_max_radius) * sin(qDegreesToRadians(-1 * current_angle))),

                            QPointF(
                                center.x() +
                                    (fuel_progress_arc_view_max_radius -
                                           fmin(width, height) * 0.05) *
                                        cos(qDegreesToRadians(-1 * current_angle)),
                                center.y() +
                                    (fuel_progress_arc_view_max_radius -
                                           fmin(width, height) * 0.05) *
                                        sin(qDegreesToRadians(-1 * current_angle))));



          current_angle += fuel_progress_child_arc_length;
        }

}

void SpeedMeter::draw_dynamic_speed_text(QPainter *painter, QPen *pen, QBrush *brush, qreal value) {
    QPointF speed_text_center { painter->window().center()};

    qreal width {static_cast<qreal>(painter->window().width())};
    qreal height { static_cast<qreal>(painter->window().height())};

    QFont *dynamic_speed_font {new QFont("Arial", fmin(width, height) * 0.1)};
    pen->setColor(Qt::white);
    painter->setPen(*pen);
    brush->setColor(Qt::transparent);
    painter->setBrush(*brush);
    painter->setFont(*dynamic_speed_font);

    QString speed_text { std::to_string((int)(240.0 * value)).data()};

    QFontMetrics *fontMetrics = new QFontMetrics(painter->font());

    qreal speedTextWidth { static_cast<qreal>(fontMetrics->horizontalAdvance(speed_text))};
    qreal speedTextHeight { static_cast<qreal>(fontMetrics->height())};

    speed_text_center.setX(speed_text_center.x() - speedTextWidth * 0.5);
    speed_text_center.setY(speed_text_center.y() - speedTextHeight * 0.5);

    painter->drawText(speed_text_center, speed_text);

    delete fontMetrics;
    delete dynamic_speed_font;
}

void SpeedMeter::draw_dynamic_speed_measurement_unit_text(QPainter *painter, QPen *pen, QBrush *brush) {
    QPointF speed_text_center { painter->window().center()};

    qreal width {static_cast<qreal>(painter->window().width())};
    qreal height { static_cast<qreal>(painter->window().height())};

    QFont *dynamic_speed_measurement_unit_font { new QFont("Arial", fmin(width, height) * 0.05)};
    pen->setColor(Qt::white);
    painter->setPen(*pen);
    brush->setColor(Qt::transparent);
    painter->setBrush(*brush);
    painter->setFont(*dynamic_speed_measurement_unit_font);

    QString speed_text { "km/h"};

    QFontMetrics *fontMetrics = new QFontMetrics(painter->font());

    qreal speed_measurement_unit_text_width { static_cast<qreal>(fontMetrics->horizontalAdvance(speed_text))};
    qreal speed_measurement_unit_text_height { static_cast<qreal>(fontMetrics->height())};

    speed_text_center.setX(speed_text_center.x() - speed_measurement_unit_text_width * 0.5);
    speed_text_center.setY(speed_text_center.y() + speed_measurement_unit_text_height * 0.5);

    painter->drawText(speed_text_center, speed_text);

    delete fontMetrics;
    delete dynamic_speed_measurement_unit_font;
}

