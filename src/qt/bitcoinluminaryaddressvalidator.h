// Copyright (c) 2011-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOINLUMINARY_QT_BITCOINLUMINARYADDRESSVALIDATOR_H
#define BITCOINLUMINARY_QT_BITCOINLUMINARYADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BitcoinLuminaryAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BitcoinLuminaryAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** BitcoinLuminary address widget validator, checks for a valid bitcoinluminary address.
 */
class BitcoinLuminaryAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BitcoinLuminaryAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // BITCOINLUMINARY_QT_BITCOINLUMINARYADDRESSVALIDATOR_H
