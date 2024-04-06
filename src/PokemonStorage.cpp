#include "../include/PokemonStorage.hpp"
#include <ctime>

Storage::Pokemons::PokemonStorage::PokemonStorage()
{
    _initPokemonStorage();
};

void Storage::Pokemons::PokemonStorage::_initPokemonStorage()
{
    this->m_pokemonStore.push_back(new Pokemon("Bulbasaur", "assets/pokemon/bulbasaur.png", 100, 100));
    this->m_pokemonStore.push_back(new Pokemon("Charmander", "assets/pokemon/charmander.png", 100, 100));
};

Pokemon *Storage::Pokemons::PokemonStorage::GetRandomPokemon() const
{
    srand(time(NULL));

    const unsigned short int MAX_RANGE = this->m_pokemonStore.size();

    int randomIndex = rand() % MAX_RANGE;

    return this->m_pokemonStore[randomIndex];
}
