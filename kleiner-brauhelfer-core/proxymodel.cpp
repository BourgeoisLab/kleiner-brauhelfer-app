#include "proxymodel.h"
#include "sqltablemodel.h"

ProxyModel::ProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    mDeletedColumn(-1),
    mDateColumn(-1),
    mMinDate(QDateTime()),
    mMaxDate(QDateTime())
{
    setDynamicSortFilter(false);
    setFilterCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
}

void ProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);
    if(SqlTableModel* model = dynamic_cast<SqlTableModel*>(sourceModel))
        mDeletedColumn = model->fieldIndex("deleted");
    else if(ProxyModel* model = dynamic_cast<ProxyModel*>(sourceModel))
        mDeletedColumn = model->fieldIndex("deleted");
    else
        mDeletedColumn = -1;
    connect(sourceModel, SIGNAL(modelReset()), this, SLOT(onModelReset()));
    connect(sourceModel, SIGNAL(modified()), this, SIGNAL(modified()));
    connect(sourceModel, SIGNAL(reverted()), this, SIGNAL(reverted()));
    connect(this, SIGNAL(reverted()), this, SLOT(onModelReset()));
}

void ProxyModel::onModelReset()
{
    invalidateFilter();
    sort();
}

QVariant ProxyModel::data(int row, const QString &fieldName, int role) const
{
    return data(index(row, fieldIndex(fieldName)), role);
}

bool ProxyModel::setData(int row, const QString &fieldName, const QVariant &value, int role)
{
    return setData(index(row, fieldIndex(fieldName)), value, role);
}

bool ProxyModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (QSortFilterProxyModel::removeRows(row, count, parent))
    {
        invalidateFilter();
        sort();
        return true;
    }
    return false;
}

bool ProxyModel::removeRow(int arow, const QModelIndex &parent)
{
    if (QSortFilterProxyModel::removeRow(arow, parent))
    {
        invalidateFilter();
        sort();
        return true;
    }
    return false;
}

int ProxyModel::append(const QVariantMap &values)
{
    SqlTableModel* model = dynamic_cast<SqlTableModel*>(sourceModel());
    if (model)
    {
        int idx = model->append(values);
        invalidateFilter();
        sort();
        return mapRowFromSource(idx);
    }
    ProxyModel* proxyModel = dynamic_cast<ProxyModel*>(sourceModel());
    if (proxyModel)
    {
        int idx = proxyModel->append(values);
        invalidateFilter();
        sort();
        return mapRowFromSource(idx);
    }
    return -1;
}

int ProxyModel::mapRowToSource(int row) const
{
    QModelIndex index = mapToSource(this->index(row, 0));
    return index.row();
}

int ProxyModel::mapRowFromSource(int row) const
{
    QModelIndex index = mapFromSource(sourceModel()->index(row, 0));
    return index.row();
}

int ProxyModel::fieldIndex(const QString &fieldName) const
{
    SqlTableModel* model = dynamic_cast<SqlTableModel*>(sourceModel());
    if (model)
        return model->fieldIndex(fieldName);
    ProxyModel* proxyModel = dynamic_cast<ProxyModel*>(sourceModel());
    if (proxyModel)
        return proxyModel->fieldIndex(fieldName);
    return -1;
}

int ProxyModel::getRowWithValue(const QString &fieldName, const QVariant &value)
{
    SqlTableModel* model = dynamic_cast<SqlTableModel*>(sourceModel());
    if (model)
        return mapRowFromSource(model->getRowWithValue(fieldName, value));
    ProxyModel* proxyModel = dynamic_cast<ProxyModel*>(sourceModel());
    if (proxyModel)
        return mapRowFromSource(proxyModel->getRowWithValue(fieldName, value));
    return -1;
}

QVariant ProxyModel::getValueFromSameRow(const QString &fieldNameKey, const QVariant &valueKey, const QString &fieldName)
{
    SqlTableModel* model = dynamic_cast<SqlTableModel*>(sourceModel());
    if (model)
        return model->getValueFromSameRow(fieldNameKey, valueKey, fieldName);
    ProxyModel* proxyModel = dynamic_cast<ProxyModel*>(sourceModel());
    if (proxyModel)
        return proxyModel->getValueFromSameRow(fieldNameKey, valueKey, fieldName);
    return QVariant();
}

void ProxyModel::setFilterString(const QString &pattern)
{
    setFilterFixedString(pattern);
}

void ProxyModel::sort(int column, Qt::SortOrder order)
{
    QSortFilterProxyModel::sort(column, order);
    emit sortChanged();
}

void ProxyModel::sort()
{
    sort(sortColumn(), sortOrder());
}

int ProxyModel::sortColumn() const
{
    return QSortFilterProxyModel::sortColumn();
}

void ProxyModel::setSortColumn(int column)
{
    sort(column, sortOrder());
}

Qt::SortOrder ProxyModel::sortOrder() const
{
    return QSortFilterProxyModel::sortOrder();
}

void ProxyModel::setSortOrder(Qt::SortOrder order)
{
    sort(sortColumn(), order);
}

int ProxyModel::filterDateColumn() const
{
    return mDateColumn;
}

void ProxyModel::setFilterDateColumn(int column)
{
    mDateColumn = column;
    invalidateFilter();
    sort();
    emit filterChanged();
}

QDateTime ProxyModel::filterMinimumDate() const
{
    return mMinDate;
}

void ProxyModel::setFilterMinimumDate(const QDateTime &dt)
{
    mMinDate = dt;
    invalidateFilter();
    sort();
    emit filterChanged();
}

QDateTime ProxyModel::filterMaximumDate() const
{
    return mMaxDate;
}

void ProxyModel::setFilterMaximumDate(const QDateTime &dt)
{
    mMaxDate = dt;
    invalidateFilter();
    sort();
    emit filterChanged();
}

bool ProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool accept = QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    if (accept && mDeletedColumn >= 0)
    {
        QModelIndex index = sourceModel()->index(source_row, mDeletedColumn, source_parent);
        if (index.isValid())
            accept = !sourceModel()->data(index).toBool();
    }
    if (accept && mDateColumn >= 0)
    {
        QModelIndex index2 = sourceModel()->index(source_row, mDateColumn, source_parent);
        if (index2.isValid())
            accept = dateInRange(sourceModel()->data(index2).toDateTime());
    }
    return accept;
}

bool ProxyModel::dateInRange(const QDateTime &dt) const
{
    return (!mMinDate.isValid() || dt > mMinDate) && (!mMaxDate.isValid() || dt < mMaxDate);
}
