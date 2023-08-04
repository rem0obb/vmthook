#include "include/VMThook.hpp"
#include <iostream>
#include <stdint.h>
#include <unistd.h>

// Interface (classe abstrata)
class IPlayerClient
{
public:
    virtual void CreateMove() = 0;
    virtual void Voice() const = 0; // Método virtual puro (interface)
    virtual void VerifyPlayer() const = 0;
    virtual void Kill() const = 0;
    virtual ~IPlayerClient() {} // Destrutor virtual para permitir a exclusão polimórfica
};

// Implementação da interface
class Player : public IPlayerClient
{
public:
    virtual void CreateMove() override
    {
        std::cout << "Movendo o Reigen... " << this << std::endl;
    }

    void Voice() const override
    {
        std::cout << "Quando as coisas correm mal, não há nada de errado em fugir! (Reigen Arataka) " << this << std::endl;
    }

    void VerifyPlayer() const override
    {
        std::cout << "Reigen ainda continua vivo : )" << std::endl;
    }
    void Kill() const override
    {
        std::cout << "Reigen Morreu, o mob não estava presente." << std::endl;
    }
};

void CreateMoveHook(void *_this)
{
    std::cout << "CreateMove hooked " << _this << std::endl;
}

int main()
{
    // Criando objeto e chamando o método Voice()
    IPlayerClient *g_player = new Player;

    uint64_t *vtable = *(uint64_t **)(g_player + 0x0);

    size_t vtable_size = 0;
    while (vtable[vtable_size] != NULL)
    {
        ++vtable_size;
    }

    VMTHook vmt(vtable, vtable_size);

    *(uint64_t *)g_player = (uint64_t)vmt.VMTGetVTableCopy();

    vmt.VMTInstallHook(0, (uint64_t)&CreateMoveHook);

    g_player->CreateMove();

    delete g_player; 
    vmt.VMTDeleteVTableCopy();

    return 0;
}
