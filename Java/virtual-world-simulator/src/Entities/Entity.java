package Entities;

import App.World;
import Common.Point;
import Entities.Animals.*;
import Entities.Plants.*;

import javax.swing.*;
import java.util.HashMap;
import java.util.Map;

public abstract class Entity implements Comparable<Entity>
{
    protected ImageIcon icon;
    protected World world;
    protected char symbol;
    protected boolean isAlive;
    protected int strength;
    protected int priority;
    protected int lifespan;
    protected Point position;

    public Entity(ImageIcon icon, World world, Point position, char symbol, int strength, int priority)
    {
        this.icon = icon;
        this.world = world;
        this.position = position;
        this.symbol = symbol;
        this.isAlive = true;
        this.strength = strength;
        this.priority = priority;
        this.lifespan = 0;
    }

    @Override
    public int compareTo(Entity entity)
    {
        if(this.priority == entity.priority)
        {
            if(this.lifespan > entity.lifespan)
                return 1;
            else if(this.lifespan < entity.lifespan)
                return -1;
            else
                return 0;
        }
        else if(this.priority > entity.priority)
            return 1;
        else
            return -1;
    }

    public ImageIcon getIcon()
    {
        return this.icon;
    }

    public char getSymbol() {
        return this.symbol;
    }

    public boolean checkIfAlive() {
        return this.isAlive;
    }

    public int getStrength()
    {
        return this.strength;
    }

    public void setStrength(int value)
    {
        this.strength = value;
    }

    public int getPriority()
    {
        return this.priority;
    }

    public int getLifespan()
    {
        return this.lifespan;
    }

    public Point getPosition()
    {
        return this.position;
    }

    public void setPosition(Point position)
    {
        this.position = position;
    }

    public void Kill()
    {
        this.isAlive = false;
        world.map[position.x][position.y].setEntity(null);
    }

    public void Update()
    {
        this.lifespan++;
    }

    public boolean Collision(Entity entity)
    {
        return false;
    }

    public static Entity getEntityFromSymbol(World world, Point position, char symbol)
    {
        switch(symbol)
        {
            //case 'H': return new Human(world, position, lifeSpan, strength);
            case 'A': return new Antelope(world, position);
            case 'F': return new Fox(world, position);
            case 'S': return new Sheep(world, position);
            case 'T': return new Turtle(world, position);
            case 'W': return new Wolf(world, position);
            case 'G': return new Grass(world, position);
            case 'D': return new Dandelion(world, position);
            case 'N': return new Nightshade(world, position);
            case 'U': return new Guarana(world, position);
            case 'P': return new PineHogweed(world, position);
        }
        return null;
    }

    public static final Map<Character, String> types = new HashMap<Character, String>(){
        {
            put('H', "Human");
            put('A', "Antelope");
            put('F', "Fox");
            put('S', "Sheep");
            put('T', "Turtle");
            put('W', "Wolf");
            put('G', "Grass");
            put('D', "Dandelion");
            put('N', "Nightshade");
            put('U', "Guarana");
            put('P', "Pine Hogweed");
        }
    };
}