#ifndef TALENT_H
#define TALENT_H

#include <QObject>
#include <QString>
#include <QMap>
#include <assert.h>

class Talent: public QObject {
    Q_OBJECT
public:
    Talent(const QString& name_, const QString & position_, const QString &icon_, const int max_points_);
    virtual ~Talent();

    QString get_name() const;
    QString get_icon() const;
    QString get_position() const;
    QString get_right_arrow_image() const;
    QString get_bottom_arrow_image() const;

    // TODO: Mark as abstract class when talents are fully implemented.
    virtual void effect() {} //= 0;
    virtual QString get_requirement_string() const;
    QString get_current_rank_description() const;
    QString get_next_rank_description() const;
    int get_current_rank() const;
    int get_max_rank() const;
    bool increment_rank();
    bool decrement_rank();

    bool is_active() const;
    bool is_maxed() const;

    bool has_right_child() const;
    bool has_bottom_child() const;
    Talent* get_bottom_child() const;
    Talent* get_right_child() const;

protected:
    const QString name;
    const QString position;
    const QString icon;
    const int max_points;
    int curr_points;

    Talent* parent;
    Talent* right_child;
    Talent* bottom_child;

    QMap<int, QString> rank_descriptions;

    bool any_child_active() const;
    QString get_arrow_identifier(const QString target_position) const;

private:

};


#endif // TALENT_H
