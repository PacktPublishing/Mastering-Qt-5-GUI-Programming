#include <iostream>
#include <QImage>
#include <QVector>
#include <QColor>
#include <QFile>
#include <QDir>
#include <QRandomGenerator>
#include <QDebug>
#include <QStringList>

#include "virdis_values.h"


int main()
{
    QVector<QColor> colors = get_virdis_values();

    // Step 1: Get the current Directory
    QDir directory = QDir::current();

    // Step 2: Change into the `2_section` Directory

    bool dir_exists = directory.cd("../../2_section");
    if (!dir_exists)
    {
        qFatal("Directory `2_section` not found. Change code to `cd` into the absolute path for your system instead, or move the build to the expected directory of `master_qt/1_section/YOUR_BUILD_HERE");
        qDebug() << directory.canonicalPath();
        return 1;
    }

    // Step 3: Create a `pics` folder/directory if it does not exist
    bool pics_dir_exists = directory.exists("pics");

    if (!pics_dir_exists)
        directory.mkdir("pics");

    directory.cd("pics");

    QStringList exclude_filenames;
    exclude_filenames << "pictures.qrc";

    // Step 4: Remove all old pictures, if any
    foreach(QString filepath, directory.entryList(exclude_filenames))
        directory.remove(filepath);

    QRandomGenerator random;

    // Step 5: Generate 100 pictures and fill with a random QColor
    for (int i=0; i<100; i++)
    {
        QImage image(100,100, QImage::Format_ARGB32);
        // int random_number = qrand() % 255;
        int random_number = random.bounded(255);
        QColor color = colors[random_number];

        image.fill(color);

        QString filepath = directory.absoluteFilePath(QString::number(i) + ".png");
        qDebug() << filepath;

        image.save(filepath);
    }
}

