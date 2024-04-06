#include "../include/PokemonStorage.hpp"

Storage::Pokemons::PokemonStorage::PokemonStorage()
{
    _initPokemonStorage();
};

void Storage::Pokemons::PokemonStorage::_initPokemonStorage()
{
    this->m_pokemonStore.push_back(new Pokemon("Bulbasaur", "assets/pokemon/bulbasaur.png", 100, 100));
};

Pokemon *Storage::Pokemons::PokemonStorage::GetRandomPokemon() const
{
    return this->m_pokemonStore[0];
}
