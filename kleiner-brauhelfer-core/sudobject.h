#ifndef SUDOBJECT_H
#define SUDOBJECT_H

#include "kleiner-brauhelfer-core_global.h"
#include <QObject>
#include <QDateTime>
#include "proxymodel.h"

class Brauhelfer;

// Property with automatic getter/setter generation
#define Q_PROPERTY_SUD(type, name, convertion) \
    Q_PROPERTY(type name READ get##name WRITE set##name NOTIFY modified) \
    public: type get##name() const { return getValue(#name).convertion; } \
    public: void set##name(type const &value) { setValue(#name, value); }
#define Q_PROPERTY_SUD_READONLY(type, name, convertion) \
    Q_PROPERTY(type name READ get##name NOTIFY modified) \
    public: type get##name() const { return getValue(#name).convertion; }

class LIB_EXPORT SudObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY loadedChanged)
    Q_PROPERTY(int id READ id NOTIFY loadedChanged)

    // real fields in table Sud
    Q_PROPERTY_SUD(QString, Sudname, toString())
    Q_PROPERTY_SUD(double, Menge, toDouble())
    Q_PROPERTY_SUD(double, SW, toDouble())
    Q_PROPERTY_SUD(double, CO2, toDouble())
    Q_PROPERTY_SUD(int, IBU, toInt())
    Q_PROPERTY_SUD(QString, Kommentar, toString())
    Q_PROPERTY_SUD(int, Status, toInt())
    Q_PROPERTY_SUD(QDateTime, Braudatum, toDateTime())
    Q_PROPERTY_SUD(double, WuerzemengeAnstellen, toDouble())
    Q_PROPERTY_SUD(double, SWAnstellen, toDouble())
    Q_PROPERTY_SUD(QDateTime, Abfuelldatum, toDateTime())
    Q_PROPERTY_SUD(double, SWSchnellgaerprobe, toDouble())
    Q_PROPERTY_SUD(double, SWJungbier, toDouble())
    Q_PROPERTY_SUD(double, TemperaturJungbier, toDouble())
    Q_PROPERTY_SUD(double, WuerzemengeKochende, toDouble())
    Q_PROPERTY_SUD(double, Speisemenge, toDouble())
    Q_PROPERTY_SUD(double, SWKochende, toDouble())
    Q_PROPERTY_SUD(double, FaktorHauptguss, toDouble())
    Q_PROPERTY_SUD(int, KochdauerNachBitterhopfung, toInt())
    Q_PROPERTY_SUD(int, EinmaischenTemp, toInt())
    Q_PROPERTY_SUD(QDateTime, Erstellt, toDateTime())
    Q_PROPERTY_SUD(QDateTime, Gespeichert, toDateTime())
    Q_PROPERTY_SUD(double, erg_S_Gesamt, toDouble())
    Q_PROPERTY_SUD(double, erg_W_Gesamt, toDouble())
    Q_PROPERTY_SUD(double, erg_WHauptguss, toDouble())
    Q_PROPERTY_SUD(double, erg_WNachguss, toDouble())
    Q_PROPERTY_SUD(double, erg_Sudhausausbeute, toDouble())
    Q_PROPERTY_SUD(double, erg_Farbe, toDouble())
    Q_PROPERTY_SUD(double, erg_Preis, toDouble())
    Q_PROPERTY_SUD(double, erg_Alkohol, toDouble())
    Q_PROPERTY_SUD(double, KostenWasserStrom, toDouble())
    Q_PROPERTY_SUD(int, Reifezeit, toInt())
    Q_PROPERTY_SUD(int, Nachisomerisierungszeit, toInt())
    Q_PROPERTY_SUD(double, WuerzemengeVorHopfenseihen, toDouble())
    Q_PROPERTY_SUD(double, erg_EffektiveAusbeute, toDouble())
    Q_PROPERTY_SUD(double, RestalkalitaetSoll, toDouble())
    Q_PROPERTY_SUD(bool, SchnellgaerprobeAktiv, toBool())
    Q_PROPERTY_SUD(double, JungbiermengeAbfuellen, toDouble())
    Q_PROPERTY_SUD(double, erg_AbgefuellteBiermenge, toDouble())
    Q_PROPERTY_SUD(int, berechnungsArtHopfen, toInt())
    Q_PROPERTY_SUD(int, highGravityFaktor, toInt())
    Q_PROPERTY_SUD(QString, Anlage, toString())
    Q_PROPERTY_SUD(bool, AusbeuteIgnorieren, toBool())
    Q_PROPERTY_SUD(int, MerklistenID, toInt())
    Q_PROPERTY_SUD(bool, Spunden, toBool())
    Q_PROPERTY_SUD(int, Sudnummer, toInt())
    Q_PROPERTY_SUD(QString, Wasserprofil, toString())

    // virtual fields in table Sud
    Q_PROPERTY_SUD_READONLY(double, SWIst, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SREIst, toDouble())
    Q_PROPERTY_SUD_READONLY(double, MengeIst, toDouble())
    Q_PROPERTY_SUD_READONLY(double, IbuIst, toDouble())
    Q_PROPERTY_SUD_READONLY(double, FarbeIst, toDouble())
    Q_PROPERTY_SUD_READONLY(double, CO2Ist, toDouble())
    Q_PROPERTY_SUD_READONLY(double, Spundungsdruck, toDouble())
    Q_PROPERTY_SUD_READONLY(double, Gruenschlauchzeitpunkt, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SpeiseNoetig, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SpeiseAnteil, toDouble())
    Q_PROPERTY_SUD_READONLY(double, ZuckerAnteil, toDouble())
    Q_PROPERTY_SUD_READONLY(int, ReifezeitDelta, toInt())
    Q_PROPERTY_SUD_READONLY(bool, AbfuellenBereitZutaten, toBool())
    Q_PROPERTY_SUD_READONLY(double, MengeSollKochbeginn, toDouble())
    Q_PROPERTY_SUD_READONLY(double, MengeSollKochende, toDouble())
    Q_PROPERTY_SUD(double, WuerzemengeAnstellenTotal, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SW_Malz, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SW_WZ_Maischen, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SW_WZ_Kochen, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SW_WZ_Gaerung, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SWSollKochbeginn, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SWSollKochbeginnMitWz, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SWSollKochende, toDouble())
    Q_PROPERTY_SUD_READONLY(double, SWSollAnstellen, toDouble())
    Q_PROPERTY_SUD_READONLY(double, AnlageVerdampfungsziffer, toDouble())
    Q_PROPERTY_SUD_READONLY(double, Verdampfungsziffer, toDouble())
    Q_PROPERTY_SUD_READONLY(double, sEVG, toDouble())
    Q_PROPERTY_SUD_READONLY(double, tEVG, toDouble())
    Q_PROPERTY_SUD_READONLY(double, AnlageSudhausausbeute, toDouble())
    Q_PROPERTY_SUD_READONLY(double, RestalkalitaetFaktor, toDouble())
    Q_PROPERTY_SUD_READONLY(double, FaktorHauptgussEmpfehlung, toDouble())
    Q_PROPERTY_SUD_READONLY(int, BewertungMittel, toInt())

    // tables
    Q_PROPERTY(ProxyModel* modelRasten READ modelRasten CONSTANT)
    Q_PROPERTY(ProxyModel* modelMalzschuettung READ modelMalzschuettung CONSTANT)
    Q_PROPERTY(ProxyModel* modelHopfengaben READ modelHopfengaben CONSTANT)
    Q_PROPERTY(ProxyModel* modelHefegaben READ modelHefegaben CONSTANT)
    Q_PROPERTY(ProxyModel* modelWeitereZutatenGaben READ modelWeitereZutatenGaben CONSTANT)
    Q_PROPERTY(ProxyModel* modelSchnellgaerverlauf READ modelSchnellgaerverlauf CONSTANT)
    Q_PROPERTY(ProxyModel* modelHauptgaerverlauf READ modelHauptgaerverlauf CONSTANT)
    Q_PROPERTY(ProxyModel* modelNachgaerverlauf READ modelNachgaerverlauf CONSTANT)
    Q_PROPERTY(ProxyModel* modelBewertungen READ modelBewertungen CONSTANT)
    Q_PROPERTY(ProxyModel* modelAnhang READ modelAnhang CONSTANT)
    Q_PROPERTY(ProxyModel* modelFlaschenlabel READ modelFlaschenlabel CONSTANT)
    Q_PROPERTY(ProxyModel* modelFlaschenlabelTags READ modelFlaschenlabelTags CONSTANT)

public:

    /**
     * @brief Creates a brew object
     * @param bh Brauhelfer class
     */
    SudObject(Brauhelfer *bh);
    ~SudObject();

    /**
     * @brief Loads a brew
     * @param id Brew ID
     */
    Q_INVOKABLE void load(int id);

    /**
     * @brief Unload any loaded brew
     */
    Q_INVOKABLE void unload();

    /**
     * @brief Loading state
     * @return True if a brew is being loaded
     */
    bool isLoading() const;

    /**
     * @brief Loaded state
     * @return True if a brew is loaded
     */
    bool isLoaded() const;

    /**
     * @brief Gets the brew ID
     * @return Brew ID
     */
    int id() const;

    /**
     * @brief Gets the row inside the Sud model
     * @return
     */
    int row() const;

    /**
     * @brief Gets a value
     * @param fieldName Field name
     * @return Value
     */
    QVariant getValue(const QString &fieldName) const;

    /**
     * @brief Sets a value
     * @param fieldName Field name
     * @param value Field value
     * @return True on success
     */
    bool setValue(const QString &fieldName, const QVariant &value);

    /**
     * @brief getAnlageValue
     * @param fieldName
     * @return
     */
    QVariant getAnlageData(const QString& fieldName) const;

    /**
     * @brief getWasserValue
     * @param fieldName
     * @return
     */
    QVariant getWasserData(const QString& fieldName) const;

    /**
     * @brief Gets the different tables
     * @return Table model
     */
    ProxyModel* modelRasten() const;
    ProxyModel* modelMalzschuettung() const;
    ProxyModel* modelHopfengaben() const;
    ProxyModel* modelHefegaben() const;
    ProxyModel* modelWeitereZutatenGaben() const;
    ProxyModel* modelSchnellgaerverlauf() const;
    ProxyModel* modelHauptgaerverlauf() const;
    ProxyModel* modelNachgaerverlauf() const;
    ProxyModel* modelBewertungen() const;
    ProxyModel* modelAnhang() const;
    ProxyModel* modelFlaschenlabel() const;
    ProxyModel* modelFlaschenlabelTags() const;

    /**
     * @brief Substracts the brew ingredients from the inventory
     */
    Q_INVOKABLE void brauzutatenAbziehen();

    /**
     * @brief Substracts an ingredient from the inventory
     * @param ingredient Ingredient
     * @param typ 0: Hopfen, 1: Hefe, 2: weitere Zutat
     * @param quantity Quantity [g]
     */
    Q_INVOKABLE void zutatAbziehen(const QString& zutat, int typ, double menge);

Q_SIGNALS:

    /**
     * @brief dataChanged
     * @param topLeft
     * @param bottomRight
     * @param roles
     */
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

    /**
     * @brief Emitted when something was modified
     */
    void modified();

    /**
     * @brief Emitted when a brew was loaded or unloaded
     */
    void loadedChanged();

private slots:
    void onSudLayoutChanged();
    void onSudDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

private:
    Brauhelfer *bh;
    int mId;
    int mRowSud;
    bool mLoading;
    ProxyModel* proxyModelRasten;
    ProxyModel* proxyModelMalzschuettung;
    ProxyModel* proxyModelHopfengaben;
    ProxyModel* proxyModelHefegaben;
    ProxyModel* proxyModelWeitereZutatenGaben;
    ProxyModel* proxyModelSchnellgaerverlauf;
    ProxyModel* proxyModelHauptgaerverlauf;
    ProxyModel* proxyModelNachgaerverlauf;
    ProxyModel* proxyModelBewertungen;
    ProxyModel* proxyModelAnhang;
    ProxyModel* proxyModelFlaschenlabel;
    ProxyModel* proxyModelFlaschenlabelTags;
};

#endif // SUDOBJECT_H
