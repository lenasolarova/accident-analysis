import pandas
import pytest

import main
import mapping


@pytest.fixture
def df_all():
    return pandas.read_csv("../test.csv")


@pytest.fixture
def df_non_dup(df_all):
    return df_all.drop_duplicates(subset=["id_nehody"])


def test_caused_by_alcohol(df_non_dup):
    result = main.caused_by_alcohol(df_non_dup)
    assert result == 75.0


def test_percent_per_day(df_non_dup):
    result = main.percent_per_day(df_non_dup)
    assert set(result.keys()) == set(mapping.DAY_MAP.values())
    assert result["Monday"] == 25.0
    assert result["Friday"] == 50.0
    assert result["Sunday"] == 25.0


def test_seatbelt_injury(df_non_dup):
    result = main.seatbelt_injury(df_non_dup)
    #stav_ridic=True (pod vlivem), ozn_osoba=True (nepripoutan), nasledek
    assert result.loc[(True, True), "minor"] == 33.33
    assert result.loc[(True, True), "fatal"] == 33.33
    assert result.loc[(True, True), "none"] == 33.33
    #stav_ridic=False (nezjistovano), ozn_osoba=True (nepripoutan), nasledek='severe'
    assert result.loc[(False, True), "severe"] == 100