#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_addPButton_table_clicked();

    void on_delPButton_table_clicked();

    void on_showPButton_table_clicked();

    void on_commitPButton_table_clicked();

    void on_showPButton_import_clicked();

    void on_delPButton_import_clicked();

    void on_addPButton_import_clicked();

    void on_commitPButton_import_clicked();

    void on_addPButton_export_clicked();

    void on_delPButton_export_clicked();

    void on_showPButton_export_clicked();

    void on_commitPButton_export_clicked();

    void on_import_day_PButton_clicked();

    void on_import_week_PButton_clicked();

    void on_import_month_PButton_clicked();

    void on_import_season_Button_clicked();

    void on_import_year_PButton_clicked();

    void on_export_season_PButton_clicked();

    void on_export_day_PButton_clicked();

    void on_export_week_PButton_clicked();

    void on_export_month_PButton_clicked();

    void on_export_year_PButton_clicked();

    void on_modPButton_table_clicked();

    void createPdf();

    void on_delPButton_stock_clicked();

    void on_commitPButton_stock_clicked();

    void on_printPButton_stock_clicked();

    void on_showAllPButton_stock_clicked();

    void on_printTableWidgetPButton_clicked();

    void on_searchPButton_stock_clicked();

//    void on_clear_PButton_clicked();

    void on_clear_sta_PButton_clicked();

    void on_search_PButton_alart_clicked();

private:
    Ui::Widget *ui;
        QSqlTableModel *model,*model1,*model2,*model3;
};

#endif // WIDGET_H
