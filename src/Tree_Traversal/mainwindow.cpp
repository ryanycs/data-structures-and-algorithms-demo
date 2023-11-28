#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    draw = false;
    width = 500;
    height = 50;
    radis = 30;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter paint(this);
    paint.setBrush(Qt::white);
    paint.setFont(QFont("times",10));
    if (draw) {
        drawTree(paint, tree.root, this->size().width() / 2, 20, width);
    }
}

void MainWindow::on_InsertButton_clicked()
{
    QStringList list = ui->textEdit_2->toPlainText().split(",");
    ui->textEdit_2->setPlainText("");
    QStringList list2 = ui->textEdit->toPlainText().split(",");
    ui->textEdit->setPlainText("");

    vector<int> _preorder;
    for (QString& s: list) {
        int data = s.toInt();
        _preorder.push_back(data);
    }

    vector<int> _inorder;
    for (QString& s: list2) {
        int data = s.toInt();
        _inorder.push_back(data);
    }
    tree.build(_preorder, _inorder);
}


void MainWindow::on_DrawButton_clicked()
{
    draw = true;
    update();

    vector<int> order;
    QString text;
    order = tree.preorder();
    for (int i = 0; i < order.size(); i++) {
        text += QString::number(order[i]) + (i == order.size() - 1 ? "" : ",");
    }
    ui->PreorderBrowser->setPlainText(text);
    text.clear();

    order = tree.inorder();
    for (int i = 0; i < order.size(); i++) {
        text += QString::number(order[i]) + (i == order.size() - 1 ? "" : ",");
    }
    ui->InorderBrowser->setPlainText(text);
    text.clear();

    order = tree.posorder();
    for (int i = 0; i < order.size(); i++) {
        text += QString::number(order[i]) + (i == order.size() - 1 ? "" : ",");
    }
    ui->PosorderBrowser->setPlainText(text);
    text.clear();
}

void MainWindow::drawTree(QPainter& paint, TreeNode<int>* node, int x, int y, int w) {
    if (node == NULL)
        return;

    int curWidth = w / 2;

    paint.drawEllipse(x, y, radis, radis);

    paint.drawText(QRect(QPoint(x, y),QSize(QSize(radis,radis))), QString::number(node->val), QTextOption(Qt::AlignCenter));

    if (node->left != NULL)
        paint.drawLine(x + radis / 2, y + radis, x - curWidth + radis / 2, y + height);
    if (node->right != NULL)
       paint.drawLine(x + radis / 2, y + radis, x + curWidth + radis / 2, y + height);

    drawTree(paint, node->left, x - curWidth, y + height, curWidth);
    drawTree(paint, node->right, x + curWidth, y + height, curWidth);
}
