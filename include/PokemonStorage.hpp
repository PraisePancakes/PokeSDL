#include "Pokemon.hpp"
#include <vector>

namespace Storage
{
    namespace Pokemons
    {
        class PokemonStorage
        {
            std::vector<Pokemon *> m_pokemonStore;
            void _initPokemonStorage();

        public:
            PokemonStorage();

            Pokemon *GetRandomPokemon() const;
        };
    };

};